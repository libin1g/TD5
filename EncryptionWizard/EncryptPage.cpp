#include "EncryptPage.h"
#include "EncryptionWizard.h"

#include <QApplication>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QByteArray>

CEncryptPage::CEncryptPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Encrypt File"));
    setSubTitle(tr("Encrypt file, please input source file,"
        " a 128-bit(16-byte) key and so on."));

    m_pKey = new QLineEdit(this);
    m_pKey->setMaxLength(BYTES_OF_KEY);
    m_pKey->setToolTip(tr("A 128-bit(16-byte) key for encryption or decryption."));
    m_pKey->setEchoMode(QLineEdit::Password);
    registerField("EncryptPage.Key*", m_pKey);
    m_pKeyLabel = new QLabel(tr("&Key:"), this);
    m_pKeyLabel->setBuddy(m_pKey);
    m_pKeyShow = new QCheckBox(tr("Display character"));
    m_pKeyShow->setChecked(false);
    connect(m_pKey, SIGNAL(editingFinished()), this, SLOT(OnEditFinished()));
    connect(m_pKeyShow, SIGNAL(stateChanged(int)), SLOT(OnKeyShowChanged(int)));

    m_pSrcFile = new QLineEdit(this);
    registerField("EncryptPage.SrcFile*", m_pSrcFile);
    m_pSrcFileLabel = new QLabel(tr("&Source File:"), this);
    m_pSrcFileLabel->setBuddy(m_pSrcFile);
    m_pSrcFileBrowser = new QPushButton(tr("&Browser..."), this);
    connect(m_pSrcFileBrowser, SIGNAL(pressed()), SLOT(OnSrcFileBrowserPressed()));

    m_pDstFile = new QLineEdit(this);;
    registerField("EncryptPage.DstFile*", m_pDstFile);
    m_pDstFileLabel = new QLabel(tr("&Destination File:"), this);
    m_pDstFileLabel->setBuddy(m_pDstFile);
    m_pDstFileBrowser = new QPushButton(tr("B&rowser..."), this);
    connect(m_pDstFileBrowser, SIGNAL(pressed()), SLOT(OnDstFileBrowserPressed()));

    QGridLayout* pGridLayout = new QGridLayout(this);
    pGridLayout->addWidget(m_pKeyLabel, 0, 0);
    pGridLayout->addWidget(m_pKey, 0, 1);
    pGridLayout->addWidget(m_pKeyShow, 1, 1);
    pGridLayout->addWidget(m_pSrcFileLabel, 2, 0);
    pGridLayout->addWidget(m_pSrcFile, 2, 1);
    pGridLayout->addWidget(m_pSrcFileBrowser, 2, 2);
    pGridLayout->addWidget(m_pDstFileLabel, 3, 0);
    pGridLayout->addWidget(m_pDstFile, 3, 1);
    pGridLayout->addWidget(m_pDstFileBrowser, 3, 2);
    setLayout(pGridLayout);
}

CEncryptPage::~CEncryptPage()
{

}

int CEncryptPage::nextId() const
{ 
    return CEncryptionWizard::PAGE_CONCLUSION;
}

void CEncryptPage::initializePage()
{
    setCommitPage(true);

    wizard()->setButtonText(QWizard::BackButton, tr("Back"));
    wizard()->setButtonText(QWizard::NextButton, tr("Next"));
    wizard()->setButtonText(QWizard::FinishButton, tr("Finish"));
    wizard()->setButtonText(QWizard::CancelButton, tr("Cancel"));
    wizard()->setButtonText(QWizard::HelpButton, tr("Help"));
    wizard()->setButtonText(QWizard::CommitButton, tr("Ok"));
}

bool CEncryptPage::validatePage()
{
    bool bRet = QWizardPage::validatePage();
    QString strLastMsg = QString(tr("The lenth of key is %1 byte, "
        "a 128-bit(16-byte) key required."));

    int nSize = m_pKey->text().toLocal8Bit().size();
    if (nSize != BYTES_OF_KEY) 
    {
        QMessageBox::warning(this, tr("Warning"), strLastMsg.arg(nSize));
        m_pKey->clear();
        bRet = false;
    }
    else if (!QFile::exists(m_pSrcFile->text()))
    {
        strLastMsg = QString(tr("File \"%1\" is not exists."));
        QMessageBox::warning(this, tr("Warning"), strLastMsg.arg(m_pSrcFile->text()));
        m_pSrcFile->clear();
        bRet = false;
    }
    else
    {
        if (QMessageBox::warning(this, tr("Warning"), 
            tr("Make sure the input is correct, this page cannot be undone."),
            QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok)
            == QMessageBox::Cancel)
        {
            bRet = false;
        }

        setField("EncryptPage.Key", 
            QVariant::fromValue(m_pKey->text().toLocal8Bit()));
        setField("EncryptPage.SrcFile", m_pSrcFile->text());
        setField("EncryptPage.DstFile", m_pDstFile->text());
    }

    return bRet;
}

void CEncryptPage::OnEditFinished()
{
}


void CEncryptPage::OnKeyShowChanged(int nState)
{
    m_pKeyShow->isChecked() ? m_pKey->setEchoMode(QLineEdit::Normal)
        : m_pKey->setEchoMode(QLineEdit::Password);
}


void CEncryptPage::OnSrcFileBrowserPressed()
{
    QString strSrcFile = QFileDialog::getOpenFileName(this);

    m_pSrcFile->setText(strSrcFile);

}


void CEncryptPage::OnDstFileBrowserPressed()
{
    QString strDstFile = QFileDialog::getSaveFileName(this, tr("Save File"),
        qApp->applicationDirPath());

    m_pDstFile->setText(strDstFile);

}
