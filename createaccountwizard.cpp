#include "createaccountwizard.h"
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLineEdit>

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
    _lastNameLineEdit->setPlaceholderText("Last name");

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QHBoxLayout *nameSectionHorizontalLayout = new QHBoxLayout;
    nameSectionHorizontalLayout->addWidget(_firstNameLineEdit);
    nameSectionHorizontalLayout->addWidget(_lastNameLineEdit);

    mainLayout->addLayout(nameSectionHorizontalLayout);

    this->setLayout(mainLayout);
}
