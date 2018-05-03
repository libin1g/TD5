#include "ConclusionPage.h"

#include <QPalette>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QMessageBox>


CConclusionPage::CConclusionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Please wait..."));
    //setSubTitle(tr("In cryptography, the Tiny Encryption Algorithm (TEA) "
    //    "is a block cipher. It was designed by David Wheeler and Roger Needham "
    //    "of the Cambridge Computer Laboratory; it was first presented at the "
    //    "Fast Software Encryption workshop in Leuven in 1994, and first published"
    //    "in the proceedings of that workshop."));

    m_pProgressBar = new QProgressBar(this);
    const short nBarMax= 100;
    const short nBarMin= 0;
    m_pProgressBar->setMaximum(nBarMax);
    m_pProgressBar->setMinimum(nBarMin);
    m_pProgressBar->setFormat("%p%");
    m_pProgressBar->setTextVisible(true);

    m_pPlainTextEdit = new QPlainTextEdit(this);
    m_pPlainTextEdit->setReadOnly(true);
    m_pPlainTextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
    QPalette palette = m_pPlainTextEdit->palette();
    palette.setColor(QPalette::Active, QPalette::Base, QColor(234, 234, 234)); 
    palette.setColor(QPalette::Inactive, QPalette::Base, QColor(234, 234, 234));
    m_pPlainTextEdit->setPalette(palette);

    QVBoxLayout* pVLayout = new QVBoxLayout(this);
    pVLayout->addWidget(m_pProgressBar);
    pVLayout->addWidget(m_pPlainTextEdit);
    setLayout(pVLayout);
     
    m_pThread = NULL;
    m_pTeaWorker = NULL;
}

CConclusionPage::~CConclusionPage()
{ 
    if (m_pThread && !m_pThread->isFinished())
    {
        m_pThread->terminate();
        m_pThread->wait();
        delete m_pThread;
        m_pThread = NULL;
    }

    if (m_pTeaWorker)
    {
        delete m_pTeaWorker;
        m_pTeaWorker = NULL;
    }
}

bool CConclusionPage::isComplete() const
{
    return m_pProgressBar->value() == m_pProgressBar->maximum();
}

bool CConclusionPage::IsEncrypt()
{
    return field("WelcomePage.RadioBtnEncrypt").toBool();
}

bool CConclusionPage::IsDecrypt()
{
    return field("WelcomePage.RadioBtnDecrypt").toBool();
}

void CConclusionPage::initializePage()
{
    wizard()->setButtonText(QWizard::BackButton, tr("Back"));
    wizard()->setButtonText(QWizard::NextButton, tr("Next"));
    wizard()->setButtonText(QWizard::FinishButton, tr("Finish"));
    wizard()->setButtonText(QWizard::CancelButton, tr("Cancel"));
    wizard()->setButtonText(QWizard::HelpButton, tr("Help"));
    wizard()->setButtonText(QWizard::CommitButton, tr("Ok"));

    QString strPrefix; 
    IsEncrypt() ? strPrefix = "EncryptPage" 
        : strPrefix = "DecryptPage";
    m_aKey = field(strPrefix + ".Key").toByteArray();
    m_strSrcFile = field(strPrefix + ".SrcFile").toString();
    m_strDstFile = field(strPrefix + ".DstFile").toString();
    
    m_pTeaWorker = new CTEAWorker;
    m_pThread = new QThread;
    m_pThread->start();
    m_pTeaWorker->moveToThread(m_pThread);

    connect(this, SIGNAL(encrypt(const QString, const QString, const QByteArray)), 
        m_pTeaWorker, SLOT(DoEncryptWork(const QString, const QString, const QByteArray))); 
    connect(this, SIGNAL(decrypt(const QString, const QString, const QByteArray)), 
        m_pTeaWorker, SLOT(DoDecryptWork(const QString, const QString, const QByteArray))); 
    connect(m_pTeaWorker, SIGNAL(echo(const QString)), 
        this, SLOT(OnWorkerEcho(const QString)), Qt::BlockingQueuedConnection);
    connect(m_pTeaWorker, SIGNAL(completed(double)), 
        this, SLOT(OnWorkerCompleted(double)), Qt::BlockingQueuedConnection);

    IsEncrypt() ? emit encrypt(m_strSrcFile, m_strDstFile, m_aKey) 
        : emit decrypt(m_strSrcFile, m_strDstFile, m_aKey);
}


void CConclusionPage::OnWorkerEcho(const QString strMsg)
{
    m_pPlainTextEdit->appendPlainText(strMsg);

    QScrollBar* pVBar = m_pPlainTextEdit->verticalScrollBar();
    if (pVBar && pVBar->isVisible())
    {
        pVBar->setValue(pVBar->maximum());
    }
}

void CConclusionPage::OnWorkerCompleted(double dPercent)
{
    m_pProgressBar->setValue(dPercent * 100.00);
    if (m_pProgressBar->value() == m_pProgressBar->maximum())
    {
        emit completeChanged();
    }
}

