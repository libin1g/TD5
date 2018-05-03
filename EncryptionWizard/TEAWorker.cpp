#include "TEAWorker.h"
#include "EncryptionWizard.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QDataStream>
#include <QRegExp>

CTEAWorker::CTEAWorker(QObject *parent)
    : QObject(parent)
{

}

CTEAWorker::~CTEAWorker()
{

}


void CTEAWorker::DoEncryptWork(const QString strSrcFile, 
        const QString strDstFile, const QByteArray aKey)
{
    if (QFile::exists(strSrcFile))
    {
        emit echo(tr("Ready to open file."));
        QFile inFile(strSrcFile);
        if (inFile.open(QIODevice::ReadOnly))
        {
            //>1. ready in file
            QDataStream in(&inFile);

            QString strOutTemp = strDstFile + ".cache";
            QFile outFile(strOutTemp);
            if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
            {
                emit echo(QString(tr("Warning, can not write and truncate file \"%1\" ")).arg(strOutTemp));
                int nIdx = strDstFile.lastIndexOf("\\");
                if (nIdx < 0)
                {
                    nIdx = strDstFile.lastIndexOf("/");
                }
                strOutTemp = qApp->applicationDirPath() + "/"
                    + strDstFile.right(strDstFile.length() - nIdx - 1).replace(QRegExp("\\W"), ".")
                    + ".cache";
                outFile.setFileName(strOutTemp);
                emit echo(QString(tr("Try to write and truncate file:\"%1\" ")).arg(strOutTemp));
                outFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
            }
            if (outFile.isOpen())
            {
                //>2. ready out file
                QDataStream out(&outFile); 
                //>3. ready TEA tool
                byte* key = (byte*)(aKey.constData());
                //[importent] write the user key(encrypted by a default key) to file, 
                byte aKeyKey[BYTES_OF_KEY]; 
                memset(aKeyKey, 0, BYTES_OF_KEY);
                memcpy(aKeyKey, "0123456789ABCDEF", BYTES_OF_KEY);
                m_pTeaTool = new TEA(aKeyKey);
                byte* pCipherKey = new byte[BYTES_OF_KEY];
                memset(pCipherKey, 0, BYTES_OF_KEY);
                m_pTeaTool->Encrypt(key, pCipherKey);
                m_pTeaTool->Encrypt(key + BYTES_OF_DATA_BLOCK, pCipherKey + BYTES_OF_DATA_BLOCK);
                if (out.writeRawData((const char*)pCipherKey, BYTES_OF_KEY) == BYTES_OF_KEY)
                { 
                    delete pCipherKey;
                    pCipherKey = NULL;
                    m_pTeaTool->SetKey(key);
                    //>4. encrypt BYTES_OF_DATA_BLOCK bytes once time
                    double dV = 0.0;
                    unsigned long nFileSize = inFile.size();
                    unsigned long nBytesRead = 0;
                    byte* pInByte = new byte[BYTES_OF_DATA_BLOCK];
                    byte* pOutByte = new byte[BYTES_OF_DATA_BLOCK];
                    while (!in.atEnd())
                    {
                        memset(pInByte, 0, BYTES_OF_DATA_BLOCK);
                        memset(pOutByte, 0, BYTES_OF_DATA_BLOCK);
                        int nBytes = in.readRawData((char*)pInByte, BYTES_OF_DATA_BLOCK);
                        if (nBytes < 0)
                        {
                            emit echo(QString(tr("Error, input stream status id = %1").arg(in.status())));
                            break;
                        }
                        emit echo(QString("Read  [%1]\t%2").arg(BytesToHexString(pInByte, BYTES_OF_DATA_BLOCK), -23)
                            .arg(BytesToString(pInByte, BYTES_OF_DATA_BLOCK), -8));
                        m_pTeaTool->Encrypt(pInByte, pOutByte);
                        nBytes = out.writeRawData((const char*)pOutByte, BYTES_OF_DATA_BLOCK);
                        if (nBytes < 0)
                        {
                            emit echo(QString(tr("Error, out stream status id = %1").arg(out.status())));
                            break;
                        }
                        emit echo(QString("Write [%1]\t%2").arg(BytesToHexString(pOutByte, BYTES_OF_DATA_BLOCK), -23)
                            .arg(BytesToString(pOutByte, BYTES_OF_DATA_BLOCK), -8));

                        nBytesRead += BYTES_OF_DATA_BLOCK;
                        dV = nBytesRead * 1.0 / nFileSize;
                        if (nBytesRead >= nFileSize) 
                        {
                            dV = 1.0;
                        }
                        emit completed(dV);
                    }
                    delete pInByte;
                    pInByte = NULL;
                    delete pOutByte;
                    pOutByte = NULL;

                    //>5. delete tool
                    delete m_pTeaTool;
                    m_pTeaTool = NULL;

                    //>6. rename file
                    outFile.close();
                    if (!QFile::rename(strOutTemp, strOutTemp.left(strOutTemp.lastIndexOf(".cache"))))
                    {
                        emit echo(QString(tr("Warning, we have written a cache file instead of \n"
                            "the destination file, maybe it's already exists.")));
                    }
                }
                else
                {
                    emit echo(QString(tr("Error, output stream status id = %1").arg(out.status())));
                    delete pCipherKey;
                    pCipherKey = NULL;
                }
            }
            else
            {
                emit echo(outFile.errorString());
            }
            inFile.close();
        }
        else
        {
            emit echo(inFile.errorString());
        }
    }
    else
    {
        emit echo(QString(tr("File \"%1\" is not exist.").arg(strSrcFile)));
        emit completed(1.0);
    }
    emit echo(QString(tr("Done.")));
}

void CTEAWorker::DoDecryptWork(const QString strSrcFile, 
        const QString strDstFile, const QByteArray aKey)
{
    if (QFile::exists(strSrcFile))
    {
        emit echo(tr("Ready to open file."));
        QFile inFile(strSrcFile);
        if (inFile.open(QIODevice::ReadOnly))
        {
            //>1. ready in file
            QDataStream in(&inFile);

            QString strOutTemp = strDstFile + ".cache";
            QFile outFile(strOutTemp);
            if (!outFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
            {
                emit echo(QString(tr("Warning, can not write and truncate file \"%1\" ")).arg(strOutTemp));
                int nIdx = strDstFile.lastIndexOf("\\");
                if (nIdx < 0)
                {
                    nIdx = strDstFile.lastIndexOf("/");
                }
                strOutTemp = qApp->applicationDirPath() + "/"
                    + strDstFile.right(strDstFile.length() - nIdx - 1).replace(QRegExp("\\W"), ".")
                    + ".cache";
                outFile.setFileName(strOutTemp);
                emit echo(QString(tr("Try to write and truncate file:\"%1\" ")).arg(strOutTemp));
                outFile.open(QIODevice::WriteOnly | QIODevice::Truncate);
            }
            if (outFile.isOpen())
            {
                //>2. ready out file
                QDataStream out(&outFile); 
                //>3. ready TEA tool
                byte* key = (byte*)(aKey.constData());
                m_pTeaTool = new TEA(key);
                //>4. decrypt BYTES_OF_DATA_BLOCK bytes once time
                double dV = 0.0;
                unsigned long nFileSize = inFile.size();
                //[importent] ignore the user cipher key(16-byte)
                in.skipRawData(BYTES_OF_KEY);
                nFileSize -= BYTES_OF_KEY;
                unsigned long nBytesRead = 0;
                byte* pInByte = new byte[BYTES_OF_DATA_BLOCK];
                byte* pOutByte = new byte[BYTES_OF_DATA_BLOCK];
                while (!in.atEnd())
                {
                    memset(pInByte, 0, BYTES_OF_DATA_BLOCK);
                    memset(pOutByte, 0, BYTES_OF_DATA_BLOCK);
                    int nBytes = in.readRawData((char*)pInByte, BYTES_OF_DATA_BLOCK);
                    if (nBytes < 0)
                    {
                        emit echo(QString(tr("Error, input stream status id = %1").arg(in.status())));
                        break;
                    }
                    emit echo(QString("Read  [%1]\t%2").arg(BytesToHexString(pInByte, BYTES_OF_DATA_BLOCK), -23)
                        .arg(BytesToString(pInByte, BYTES_OF_DATA_BLOCK), -8));
                    m_pTeaTool->Decrypt(pInByte, pOutByte);
                    nBytes = out.writeRawData((const char*)pOutByte, BYTES_OF_DATA_BLOCK);
                    if (nBytes < 0)
                    {
                        emit echo(QString(tr("Error, output stream status id = %1").arg(out.status())));
                        break;
                    }
                    emit echo(QString("Write [%1]\t%2").arg(BytesToHexString(pOutByte, BYTES_OF_DATA_BLOCK), -23)
                        .arg(BytesToString(pOutByte, BYTES_OF_DATA_BLOCK), -8));

                    nBytesRead += BYTES_OF_DATA_BLOCK;
                    dV = nBytesRead * 1.0 / nFileSize;
                    if (nBytesRead >= nFileSize) 
                    {
                        dV = 1.0;
                    }
                    emit completed(dV);
                }
                delete pInByte;
                pInByte = NULL;
                delete pOutByte;
                pOutByte = NULL;
                //>5. delete tool
                delete m_pTeaTool;
                m_pTeaTool = NULL;
                //>6. rename file
                outFile.close();
                if (!QFile::rename(strOutTemp, strOutTemp.left(strOutTemp.lastIndexOf(".cache"))))
                {
                    emit echo(QString(tr("Warning, we have written a cache file instead of \n"
                        "the destination file, maybe it's already exists.")));
                }
            }
            else
            {
                emit echo(outFile.errorString());
            }
            inFile.close();
        }
        else
        {
            emit echo(inFile.errorString());
        }
    }
    else
    {
        emit echo(QString(tr("File \"%1\" is not exist.").arg(strSrcFile)));
        emit completed(1.0);
    }
    emit echo(QString(tr("Done.")));
}

char CTEAWorker::IntToHexChar(int x) 
{
    static const char HEX[16] = {
        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9', 'A', 'B',
        'C', 'D', 'E', 'F'
    };

    return HEX[x];
}


QString CTEAWorker::BytesToHexString(const byte aBytes[] , int nSize) 
{
    QString strRet("");
    for (int i = 0; i < nSize; ++i) 
    {
        int t = aBytes[i];
        int a = t / 16;
        int b = t % 16;
        strRet.append(IntToHexChar(a));
        strRet.append(IntToHexChar(b));
        if (i != nSize - 1)
        {
            strRet.append(' ');
        }
    }

    return strRet;
}

QString CTEAWorker::BytesToString(const byte aBytes[] , int nSize) 
{
    QString strRet("");
    for (int i = 0; i < nSize; ++i)
    {
        int c = aBytes[i];
        // if it isn't a printable character
        if (c < 32 || c > 126)
        {
            c = '.';
        }
        strRet.append(c);
    }

    return strRet;
}
