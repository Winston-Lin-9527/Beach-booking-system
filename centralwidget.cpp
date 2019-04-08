#include <QLabel>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QDialog>

#include "centralwidget.h"
#include "createaccountwizard.h"

CentralWidget::CentralWidget(QWidget *parent)
{
    this->_stackedWindows = new QStackedWidget;

    _label = new QLabel("this is the bitch sport");
    _label2 = new QLabel("create account?");

    _createAccountButton = new QPushButton("create account");
    _bookingButton = new QPushButton("Make New Bookings");

    _createAccountWizard = new CreateAccountWizard;
    _createAccountWizardLayout = new QVBoxLayout;


    QGroupBox *groupBox = new QGroupBox;
    groupBox->setLayout(_createAccountWizardLayout);

    _stackedWindows->addWidget(_label);
    _stackedWindows->addWidget(groupBox);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(5);
    mainLayout->addWidget(_stackedWindows);
    mainLayout->addWidget(_createAccountButton);
    mainLayout->addWidget(_bookingButton);

    setLayout(mainLayout);

    connect(_createAccountButton, SIGNAL(clicked()), this, SLOT(createAccountButtonClicked()));
    connect(_bookingButton, SIGNAL(clicked()), this, SLOT(bookingButtonClicked()));
}

CentralWidget::~CentralWidget(){}

void CentralWidget::createAccountButtonClicked(){
    _stackedWindows->setCurrentIndex(1);
}

void CentralWidget::bookingButtonClicked(){
    _stackedWindows->setCurrentIndex(0);
}



