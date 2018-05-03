#include "WelcomePage.h"
#include "EncryptionWizard.h"

#include <QVBoxLayout>
#include <QMessageBox>
#include <QVariant>

CWelcomePage::CWelcomePage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Welcome"));

    m_pTopLabel = new QLabel(tr("This wizard will help you encrypt/decrypt your file."));
    m_pTopLabel->setWordWrap(true);

    m_pRadioBtnEncrypt = new QRadioButton(tr("Encrypt"));
    m_pRadioBtnDecrypt = new QRadioButton(tr("Decrypt"));
    m_pRadioBtnEncrypt->setChecked(true);
    registerField("WelcomePage.RadioBtnEncrypt", m_pRadioBtnEncrypt);
    registerField("WelcomePage.RadioBtnDecrypt", m_pRadioBtnDecrypt);

    QVBoxLayout* pVLayout = new QVBoxLayout;
    pVLayout->addWidget(m_pTopLabel);
    pVLayout->addWidget(m_pRadioBtnEncrypt);
    pVLayout->addWidget(m_pRadioBtnDecrypt);
    setLayout(pVLayout);
    
}

CWelcomePage::~CWelcomePage()
{

}


bool CWelcomePage::validatePage()
{
    bool bValid = QWizardPage::validatePage();
    if (bValid)
    {
        setField("WelcomePage.RadioBtnEncrypt", 
            QVariant::fromValue(m_pRadioBtnEncrypt->isChecked()));
        setField("WelcomePage.RadioBtnDecrypt", 
            QVariant::fromValue(m_pRadioBtnDecrypt->isChecked()));
    }
    return bValid;
}

int CWelcomePage::nextId() const
{
    int nNextId = 0;
    if (m_pRadioBtnEncrypt->isChecked())
    { 
        nNextId = CEncryptionWizard::PAGE_ENCRYPT; 
    }
    else
    {
        nNextId = CEncryptionWizard::PAGE_DECRYPT;
    }

    return nNextId;

}

void CWelcomePage::initializePage()
{
    wizard()->setButtonText(QWizard::BackButton, tr("Back"));
    wizard()->setButtonText(QWizard::NextButton, tr("Next"));
    wizard()->setButtonText(QWizard::FinishButton, tr("Finish"));
    wizard()->setButtonText(QWizard::CancelButton, tr("Cancel"));
    wizard()->setButtonText(QWizard::HelpButton, tr("Help"));
    wizard()->setButtonText(QWizard::CommitButton, tr("Ok"));
}
