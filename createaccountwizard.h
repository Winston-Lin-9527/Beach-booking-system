#ifndef CREATEACCOUNTWIZARD_H
#define CREATEACCOUNTWIZARD_H

#include <QWizard>

class QLabel;
class QVBoxLayout;
class QLineEdit;
class QDateEdit;
class QComboBox;
class QScrollArea;
class QCheckBox;

struct User;

class CreateAccountWizard : public QWizard
{
    Q_OBJECT

public:
    enum PageID{ Page_Intro, Page_Personal, Page_AccSetting, Page_Payment, Page_Summary };

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
    virtual bool validatePage() override;   // override member function to check password length
    bool checkPasswordValidity();

private:
    QLineEdit *_usernameLineEdit;
    QLineEdit *_passwordLineEdit;
    QLineEdit *_passwordConfirmLineEdit;
    QLineEdit *_resortNumberLineEdit;

    QLabel *_usernameLabel;
    QLabel *_passwordLabel;
    QLabel *_passwordConfirmLabel;
    QLabel *_resortNumberLabel;
};

class PaymentSettingPage : public QWizardPage
{
public:
    PaymentSettingPage();

private:
    QLineEdit *_visaCardNumber_LineEdit;
    QDateEdit *_visaExpiryDate_DateEdit;
    QLineEdit *_visaCVV_LineEdit;

    QIcon *_visaIcon;

    QLabel *_visaCardNumberLabel;
    QLabel *_visaExpiryDateLabel;
    QLabel *_visaCVVLabel;
};

/*
 * gives a summary of all the staffs entered in previous pages for final confirm
 */
class SummaryPage : public QWizardPage
{
    Q_OBJECT

public:
    SummaryPage();
    virtual bool validatePage() override;   // take advantage of the built-in mechanism

signals:
    void sendDetails(User &user);

private:
    QCheckBox *_checkBox;
    QLabel *_confirmationText;
};
