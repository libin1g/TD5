#ifndef CONCLUSIONPAGE_H
#define CONCLUSIONPAGE_H

#include <QWizardPage>
#include <QProgressBar>
#include <QtGui/QPlainTextEdit>
#include <QThread>
#include <QByteArray>

#include "EncryptionWizard.h"
#include "TEAWorker.h"


class CConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    CConclusionPage(QWidget *parent = 0);
    ~CConclusionPage();

    void initializePage();
    bool isComplete() const;

private:
    bool IsEncrypt();
    bool IsDecrypt();

signals:
    void encrypt(const QString strSrcFile, 
        const QString strDstFile, const QByteArray aKey);
    void decrypt(const QString strSrcFile, 
        const QString strDstFile, const QByteArray aKey);

private slots:
    void OnWorkerEcho(const QString strMsg);
    void OnWorkerCompleted(double dPercent);
    
private:
    QProgressBar* m_pProgressBar;
    QPlainTextEdit* m_pPlainTextEdit;
    QThread* m_pThread;
    CTEAWorker* m_pTeaWorker;

private:
    QByteArray m_aKey;
    QString m_strSrcFile;
    QString m_strDstFile;
};

#endif // CONCLUSIONPAGE_H
