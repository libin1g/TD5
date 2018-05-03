#ifndef ENCRYPTPAGE_H
#define ENCRYPTPAGE_H

#include <QWizardPage>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>

class CEncryptPage : public QWizardPage
{
    Q_OBJECT

public:
    CEncryptPage(QWidget *parent = 0);
    ~CEncryptPage();

    int nextId() const;
    bool validatePage();
    void initializePage();

private slots:
    void OnEditFinished();
    void OnKeyShowChanged(int nState);
    void OnSrcFileBrowserPressed();
    void OnDstFileBrowserPressed();

private:
    QLabel* m_pKeyLabel;
    QLineEdit* m_pKey;
    QCheckBox* m_pKeyShow;

    QLabel* m_pSrcFileLabel;
    QLineEdit* m_pSrcFile;
    QPushButton* m_pSrcFileBrowser;

    QLabel* m_pDstFileLabel;
    QLineEdit* m_pDstFile;
    QPushButton* m_pDstFileBrowser;
    
};

#endif // ENCRYPTPAGE_H
