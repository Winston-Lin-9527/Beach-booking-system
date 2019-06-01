#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QDateEdit>
#include <QComboBox>
#include <QScrollArea>
#include <QCheckBox>

#include "createaccountwizard.h"

CreateAccountWizard::CreateAccountWizard()
{
    this->setWindowTitle("Account creation wizard");

    this->setPage(Page_Intro, new IntroPage);
    this->setPage(Page_Personal, new PersonalPage);
    this->setPage(Page_AccSetting, new AccSettingPage);
    this->setPage(Page_Payment, new PaymentSettingPage);
    this->setPage(Page_Summary, new SummaryPage);

    this->setStartId(Page_Intro);

    this->setOption(HaveHelpButton, true);
    setPixmap(QWizard::LogoPixmap, QPixmap("logo.png"));

    connect(this, &QWizard::helpRequested, this, &CreateAccountWizard::displayHelp);
}

void CreateAccountWizard::displayHelp(){
    static QString lastMessage = QString();

    QString message = QString();

    switch(this->currentId()){
    case Page_Intro:{
            message = tr("This page gives an introduction of the create account process");
            break;
        }

    case Page_Personal:{
            message = tr("This page will allow you to enter your personal details");
            break;
        }
    case Page_AccSetting:{
        message = tr("Enter the password for your new account");
        break;
    }
    case Page_Summary:{
        message = tr("Click finish to go back to main screen.");
        break;
    }
    }

    if(message == lastMessage)
        message = tr("You've asked the same question twice in a roll, serious?");

    QMessageBox::information(this, "Help", message);

    lastMessage = message;
}

IntroPage::IntroPage():QWizardPage(nullptr){
    this->setTitle("Create Account");
    this->setPixmap(QWizard::WatermarkPixmap, QPixmap("watermark.png"));

    _bigLabel = new QLabel("This wizard will guide you create your account for the booking system.");
    _bigLabel->setWordWrap(true);   // this makes the text wraps to next line when view boundary is reached, basically auto 'return'

    _mainLayout = new QVBoxLayout;
    _mainLayout->addWidget(_bigLabel);
    this->setLayout(_mainLayout);
}

PersonalPage::PersonalPage():QWizardPage(nullptr){
    this->setTitle("Personal detail");
    // pixmap

    _firstNameLineEdit = new QLineEdit;
    _firstNameLineEdit->setPlaceholderText("First name");

    _lastNameLineEdit = new QLineEdit;
    _lastNameLineEdit->setPlaceholderText(tr("Last name"));

    _addressLineEdit = new QLineEdit;
    _addressLineEdit->setPlaceholderText(tr("Address"));

    _emailLineEdit = new QLineEdit;
    _emailLineEdit->setPlaceholderText("Email address");

    _DOBDateEdit = new QDateEdit;

    _sexComboBox = new QComboBox();
    _sexComboBox->addItems(QStringList() << "Male" << "Female");

    _DOBLabel = new QLabel("Date of birth:");
    _sexLabel = new QLabel("Your sex");

    this->registerField("personal.firstname*", _firstNameLineEdit);
    this->registerField("personal.lastname*", _lastNameLineEdit);
    this->registerField("personal.address*", _addressLineEdit);
    this->registerField("personal.email*", _emailLineEdit);
    this->registerField("personal.DOB", _DOBDateEdit);
    this->registerField("personal.sex", _sexComboBox);

    QGridLayout *mainLayout = new QGridLayout;

    QHBoxLayout *nameSectionHorizontalLayout = new QHBoxLayout;
    nameSectionHorizontalLayout->addWidget(_firstNameLineEdit);
    nameSectionHorizontalLayout->addWidget(_lastNameLineEdit);

    QHBoxLayout *addressHorizontalLayout = new QHBoxLayout;
    addressHorizontalLayout->addWidget(_addressLineEdit);

    QHBoxLayout *emailHorizontalLayout = new QHBoxLayout;
    emailHorizontalLayout->addWidget(_emailLineEdit);

    QHBoxLayout *DOBHorizontalLayout = new QHBoxLayout;
    DOBHorizontalLayout->addWidget(_DOBLabel);
    DOBHorizontalLayout->addWidget(_DOBDateEdit);

    QHBoxLayout *sexHorizontalLayout = new QHBoxLayout;
    sexHorizontalLayout->addWidget(_sexLabel);
    sexHorizontalLayout->addWidget(_sexComboBox);

    mainLayout->addLayout(nameSectionHorizontalLayout, 0, 0, Qt::AlignTop);
    mainLayout->addLayout(addressHorizontalLayout, 1, 0, Qt::AlignTop);
    mainLayout->addLayout(emailHorizontalLayout, 2, 0, Qt::AlignTop);
    mainLayout->addLayout(DOBHorizontalLayout, 3, 0, Qt::AlignTop);
    mainLayout->addLayout(sexHorizontalLayout, 4, 0, Qt::AlignTop);

    this->setLayout(mainLayout);
}

AccSettingPage::AccSettingPage():QWizardPage(nullptr){
    this->setTitle("Account setting");
    // pixmap

    _usernameLineEdit = new QLineEdit;
    _usernameLineEdit->setMaxLength(10);
    _usernameLineEdit->setMaximumWidth(150);

    _passwordLineEdit = new QLineEdit;
    _passwordLineEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    _passwordLineEdit->setMaxLength(8);
    _passwordLineEdit->setMaximumWidth(150);

    _passwordConfirmLineEdit = new QLineEdit;
    _passwordConfirmLineEdit->setEchoMode(QLineEdit::Password);
    _passwordConfirmLineEdit->setMaxLength(8);
    _passwordConfirmLineEdit->setMaximumWidth(150);

    _resortNumberLineEdit = new QLineEdit;
    _resortNumberLineEdit->setMaxLength(4);     // resort room number are all 4 digits
    _resortNumberLineEdit->setMaximumWidth(40);

    _usernameLabel = new QLabel("Username:");
    _passwordLabel = new QLabel("Your password:");
    _passwordConfirmLabel = new QLabel("Re-enter your password:");
    _resortNumberLabel = new QLabel("Your resort room number:");

    this->registerField("Acc.username", _usernameLineEdit);
    this->registerField("Acc.password", _passwordLineEdit);
    this->registerField("Acc.resortnumber", _resortNumberLineEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QHBoxLayout *usernameHorizontalLayout = new QHBoxLayout;
    usernameHorizontalLayout->addWidget(_usernameLabel);
    usernameHorizontalLayout->addWidget(_usernameLineEdit);

    QHBoxLayout *passwordHorizontalLayout = new QHBoxLayout;
    passwordHorizontalLayout->addWidget(_passwordLabel);
    passwordHorizontalLayout->addWidget(_passwordLineEdit);

    QHBoxLayout *passwordConfirmHorizontalLayout = new QHBoxLayout;
    passwordConfirmHorizontalLayout->addWidget(_passwordConfirmLabel);
    passwordConfirmHorizontalLayout->addWidget(_passwordConfirmLineEdit);

    QHBoxLayout *resortNumberHorizontalLayout = new QHBoxLayout;
    resortNumberHorizontalLayout->addWidget(_resortNumberLabel);
    resortNumberHorizontalLayout->addWidget(_resortNumberLineEdit);

    mainLayout->addLayout(usernameHorizontalLayout);
    mainLayout->addLayout(passwordHorizontalLayout);
    mainLayout->addLayout(passwordConfirmHorizontalLayout);
    mainLayout->addLayout(resortNumberHorizontalLayout);

    this->setLayout(mainLayout);

    connect(_passwordConfirmLineEdit, &QLineEdit::editingFinished, this, &AccSettingPage::checkPasswordValidity);
}

/*
 * this function responds to password and confirm password views
 */
void AccSettingPage::checkPasswordValidity(){
    if(_passwordLineEdit->text() != _passwordConfirmLineEdit->text()){
        QMessageBox::about(this, "Warning", "Passwords don't match!");
        _passwordConfirmLineEdit->clear();
        _passwordLineEdit->clear();

        _passwordLineEdit->setFocus();      // place the cursor back to password line edit
    }
}

PaymentSettingPage::PaymentSettingPage():QWizardPage(nullptr){
    this->setTitle("Payment setting");

    _visaCardNumber_LineEdit = new QLineEdit;
    _visaCardNumber_LineEdit->setMaxLength(16);     // standard VISA card number length

    _visaExpiryDate_DateEdit = new QDateEdit;

    _visaCVV_LineEdit = new QLineEdit;
    _visaCVV_LineEdit->setMaximumWidth(30);
    _visaCVV_LineEdit->setMaxLength(3);             // CVV has 3 digits only

    _visaIcon = new QIcon("visaIcon.png");

    _visaCardNumberLabel = new QLabel("Visa card Number: ");
    _visaExpiryDateLabel = new QLabel("Visa expiry date: ");
    _visaCVVLabel = new QLabel("CVV: ");

    this->registerField("Visa.number", _visaCardNumber_LineEdit);
    this->registerField("Visa.expiryDate", _visaExpiryDate_DateEdit);
    this->registerField("Visa.CVV", _visaCVV_LineEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QHBoxLayout *visaCardNumberHorizontalLayout = new QHBoxLayout;
    visaCardNumberHorizontalLayout->addWidget(_visaCardNumberLabel);
    visaCardNumberHorizontalLayout->addWidget(_visaCardNumber_LineEdit);

    QHBoxLayout *visaExpiryDateHorizontalLayout = new QHBoxLayout;
    visaExpiryDateHorizontalLayout->addWidget(_visaExpiryDateLabel);
    visaExpiryDateHorizontalLayout->addWidget(_visaExpiryDate_DateEdit);

    QHBoxLayout *visaCVVHorizontalLayout = new QHBoxLayout;
    visaCVVHorizontalLayout->addWidget(_visaCVVLabel);
    visaCVVHorizontalLayout->addWidget(_visaCVV_LineEdit);

    mainLayout->addLayout(visaCardNumberHorizontalLayout);
    mainLayout->addLayout(visaExpiryDateHorizontalLayout);
    mainLayout->addLayout(visaCVVHorizontalLayout);

    this->setLayout(mainLayout);
}

SummaryPage::SummaryPage():QWizardPage(nullptr){
    this->setTitle("Summary");

    this->_checkBox = new QCheckBox;
    this->registerField("Summary.check", _checkBox);

    this->_confirmationText = new QLabel("I have reviewed my details and confirm they are correct.");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(_confirmationText);
    layout->addWidget(_checkBox);

    this->setLayout(layout);
}

/*
 * override this function to take advantage of the built-in mechanism instead of connecting extra signals or slots
 */
bool SummaryPage::validatePage(){
    if(this->field("Summary.check") == true){
        QMessageBox::information(this, "Success", "The account has been sucessfully created!");
        return true;    // allow exit when the checkbox is checked
    }
    else {
        QMessageBox::warning(this, "Error", "You need to confirm by checking the box");
        return false;
    }
}

