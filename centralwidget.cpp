#include <QLabel>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QDialog>

#include "centralwidget.h"
#include "createaccountwizard.h"
#include "usermodel.h"

CentralWidget::CentralWidget(QWidget *parent)
{
    _stackedWindows = new QStackedWidget;
    _createAccountWizard = new CreateAccountWizard;
    _userModel = new UserModel(this);

    _welcomeLabel = new QLabel("this is the beach sport renting system");

    _createAccountButton = new QPushButton("create account");
    _bookingButton = new QPushButton("Make New Bookings");

    _mainPage = new QWidget(this);

    _mainLayout = new QHBoxLayout;

    /*
     *  add pages to the stacked window widget
     */
    QLabel *label2 = new QLabel("ddd");

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setMargin(5);
    layout->addWidget(_welcomeLabel);
    layout->addWidget(_createAccountButton);
    layout->addWidget(_bookingButton);
    _mainPage->setLayout(layout);

    _stackedWindows->addWidget(_mainPage);
    _stackedWindows->addWidget(label2);

    _mainLayout->addWidget(_stackedWindows);

    setLayout(_mainLayout);

    connect(_createAccountButton, SIGNAL(clicked()), _createAccountWizard, SLOT(exec()));
    connect(_bookingButton, SIGNAL(clicked()), this, SLOT(bookingButtonClicked()));
}

CentralWidget::~CentralWidget(){}

void CentralWidget::bookingButtonClicked(){
    _stackedWindows->setCurrentIndex(1);
}
