#include <QtGui/QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QIcon>

#include "EncryptionWizard.h"
#include "resource.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Encryption Wizard");
    app.setApplicationVersion("1.0.0.1");

    // Install Translator
    QString strTranslatorFileName = QLatin1String("qt_");
    strTranslatorFileName += QLocale::system().name();
    QTranslator* pTranslator = new QTranslator(&app);
    if (pTranslator->load(strTranslatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
    {
        app.installTranslator(pTranslator);
    }
    
    CEncryptionWizard wizard;
    wizard.show();

    return app.exec();
}
