#ifndef CREATEACCOUNTWIZARD_H
#define CREATEACCOUNTWIZARD_H

#include <QWizard>

class QLabel;
class QVBoxLayout;

class CreateAccountWizard : public QWizard
{
    Q_OBJECT

public:
    enum { Page_Intro, Page_Personal, Page_AccSetting, Page_Finish };

    CreateAccountWizard();

private slots:
    void displayHelp();
};

#endif // CREATEACCOUNTWIZARD_H

class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage();

private:
    QLabel *_bigLabel;
    QVBoxLayout *_mainLayout;
};
