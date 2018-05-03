#ifndef TEAWORKER_H
#define TEAWORKER_H

#include <QObject>
#include <QByteArray>

#include "TEA.h"


class CTEAWorker : public QObject
{
    Q_OBJECT

public:
    CTEAWorker(QObject *parent = 0);
    ~CTEAWorker();

public slots:
    void DoEncryptWork(const QString strSrcFile, 
        const QString strDstFile, const QByteArray);
    void DoDecryptWork(const QString strSrcFile, 
        const QString strDstFile, const QByteArray);

signals:
    void echo(const QString strMsg);
    void completed(double dPercent);

private: 
    char IntToHexChar(int x); 
    QString BytesToHexString(const byte aBytes[] , int nSize);
    QString BytesToString(const byte aBytes[] , int nSize);

private:
    TEA* m_pTeaTool;
};

#endif // TEAWORKER_H
