#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QWizardPage>
#include <QLabel>
#include <QRadioButton>

class CWelcomePage : public QWizardPage
{
    Q_OBJECT

public:
    CWelcomePage(QWidget *parent = 0);
    ~CWelcomePage();

    bool validatePage();
    int nextId() const;
    void initializePage();

private:
    QLabel* m_pTopLabel;
    QRadioButton* m_pRadioBtnEncrypt;
    QRadioButton* m_pRadioBtnDecrypt;
};

#endif // WELCOMEPAGE_H
