#include "createaccountwizard.h"
#include <QPixmap>
#include <QLabel>
#include <QVBoxLayout>

CreateAccountWizard::CreateAccountWizard()
{
    this->setWindowTitle("Account creation wizard");

    this->setPage(Page_Intro, new IntroPage);
    /*  populate with other pages
     *
     */

    this->setStartId(Page_Intro);

    this->setOption(HaveHelpButton, true);
    setPixmap(QWizard::LogoPixmap, QPixmap("logo.png"));

    connect(this, &QWizard::helpRequested, this, &CreateAccountWizard::displayHelp);
}

void CreateAccountWizard::displayHelp(){

}

IntroPage::IntroPage():QWizardPage(0){
    setTitle("Create Account");
    setPixmap(QWizard::WatermarkPixmap, QPixmap("watermark.png"));

    _bigLabel = new QLabel("This wizard will guide you create your account for the booking system.");
    _bigLabel->setWordWrap(true);

    _mainLayout = new QVBoxLayout;
    _mainLayout->addWidget(_bigLabel);
    this->setLayout(_mainLayout);
}
