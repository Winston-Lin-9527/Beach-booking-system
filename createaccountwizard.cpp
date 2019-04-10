#include "createaccountwizard.h"
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QDateEdit>
#include <QComboBox>

CreateAccountWizard::CreateAccountWizard()
{
    this->setWindowTitle("Account creation wizard");

    this->setPage(Page_Intro, new IntroPage);
    this->setPage(Page_Personal, new PersonalPage);
    /*  populate with other pages
     *
     */

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
    case Page_Finish:{
        message = tr("Click finish to go back to main screen.");
        break;
    }
    }

    if(message == lastMessage)
        message = tr("You've asked the same question twice in a roll, serious?");

    QMessageBox::information(this, "Help", message);

    lastMessage = message;
}

IntroPage::IntroPage():QWizardPage(0){
    this->setTitle("Create Account");
    this->setPixmap(QWizard::WatermarkPixmap, QPixmap("watermark.png"));

    _bigLabel = new QLabel("This wizard will guide you create your account for the booking system.");
    _bigLabel->setWordWrap(true);

    _mainLayout = new QVBoxLayout;
    _mainLayout->addWidget(_bigLabel);
    this->setLayout(_mainLayout);
}

PersonalPage::PersonalPage():QWizardPage(0){
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
    _sexComboBox->addItems(QStringList() << "Male" << "Female" << "Unisex");

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

AccSettingPage::AccSettingPage():QWizardPage(0){

}
