#ifndef ENCRYPTIONWIZARD_H
#define ENCRYPTIONWIZARD_H

#include <QWizard>
#include "TEA.h"

class CEncryptionWizard : public QWizard
{
    Q_OBJECT

public:
    enum {PAGE_WELCOME, PAGE_ENCRYPT, PAGE_DECRYPT, PAGE_CONCLUSION};

public:
    CEncryptionWizard(QWidget *parent = 0);
    ~CEncryptionWizard();

private slots:
    void OnShowHelp();

};

#endif // ENCRYPTIONWIZARD_H
