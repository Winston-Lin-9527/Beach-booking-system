#ifndef CREATEACCOUNTWIZARD_H
#define CREATEACCOUNTWIZARD_H

#include <QWizard>

class QLabel;
class QVBoxLayout;
class QLineEdit;
class QDateEdit;
class QRadioButton;

class CreateAccountWizard : public QWizard
{
    Q_OBJECT

public:
    enum PageID{ Page_Intro, Page_Personal, Page_AccSetting, Page_Finish };

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

class PersonalPage : public QWizardPage
{
    Q_OBJECT

public:
    PersonalPage();

private:
    QLineEdit *_firstNameLineEdit;
    QLineEdit *_lastNameLineEdit;
    QLineEdit *_addressLineEdit;
    QLineEdit *_emailLineEdit;

    QDateEdit *_DOBLineEdit;

    QRadioButton *_maleRadioButton;
    QRadioButton *_femaleRadioButton;
    QRadioButton *_unisexRadioButton;

    // more staffs
};
