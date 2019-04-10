#ifndef CREATEACCOUNTWIZARD_H
#define CREATEACCOUNTWIZARD_H

#include <QWizard>

class QLabel;
class QVBoxLayout;
class QLineEdit;
class QDateEdit;
class QComboBox;

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


/*
 * the introduction page
 */
class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage();

private:
    QLabel *_bigLabel;
    QVBoxLayout *_mainLayout;
};

/*
 * the page that allows the user to enter his personal details
 */
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

    QDateEdit *_DOBDateEdit;

    QComboBox *_sexComboBox;

    QLabel *_DOBLabel;
    QLabel *_sexLabel;
};

/*
 * the page to set the account password and resort number
 */
class AccSettingPage : public QWizardPage
{
    Q_OBJECT

public:
    AccSettingPage();

private:
    QLineEdit *_passwordLineEdit;
    QLineEdit *_resortNumberLinEdit;
    QLineEdit *_visaCardNumber_LineEdit;
    QLineEdit *_visaExpiryDate_LineEdit;
    QLineEdit *_visaCVV_LineEdit;


};
