#include "EncryptionWizard.h"

#include <QIcon>
#include <QPixmap>
#include <QMessageBox>

#include "WelcomePage.h"
#include "EncryptPage.h"
#include "DecryptPage.h"
#include "ConclusionPage.h"


CEncryptionWizard::CEncryptionWizard(QWidget *parent) 
    : QWizard(parent)
{
    setPage(PAGE_WELCOME, new CWelcomePage);
    setPage(PAGE_ENCRYPT, new CEncryptPage);
    setPage(PAGE_DECRYPT, new CDecryptPage);
    setPage(PAGE_CONCLUSION, new CConclusionPage);
    //setPage

    setStartId(PAGE_WELCOME);
    setOption(QWizard::HaveHelpButton, true);

    connect(this, SIGNAL(helpRequested()), SLOT(OnShowHelp()));

    setWindowTitle(tr("Encryption Wizard"));
    setWindowIcon(QIcon(":/Images/Resources/lock.png"));

}

CEncryptionWizard::~CEncryptionWizard()
{

}

void CEncryptionWizard::OnShowHelp()
{
    static QString strLastMsg;

    QString strMessage;
    switch (currentId()) 
    {
        case PAGE_WELCOME:
            {
                strMessage = tr("The decision you make here will affact which page you"
                    " get to see next.");
                break;
            }
        default:
            strMessage = tr("This help is likely not to be of any help.");
            break;
    }

    if (strLastMsg == strMessage)
    {
        strMessage = tr("Sorry, I already gave what help I could."
            "Maybe you should try asking an expert.");
    }

    QMessageBox::information(this, tr("Encryption Wizard Help"), strMessage);

    strLastMsg = strMessage;

}