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

    _userModel = new UserModel(this);

    _label = new QLabel("this is the bitch sport");
    _label2 = new QLabel("create account?");

    _createAccountButton = new QPushButton("create account");
    _bookingButton = new QPushButton("Make New Bookings");

    _createAccountWizard = new CreateAccountWizard;

    /*
     *  add pages to the stacked window widget
     */
    _stackedWindows->addWidget(_label);         // first page

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(5);
    mainLayout->addWidget(_stackedWindows);
    mainLayout->addWidget(_createAccountButton);
    mainLayout->addWidget(_bookingButton);

    setLayout(mainLayout);

    connect(_createAccountButton, SIGNAL(clicked()), _createAccountWizard, SLOT(exec()));
    connect(_bookingButton, SIGNAL(clicked()), this, SLOT(bookingButtonClicked()));
}

CentralWidget::~CentralWidget(){}

void CentralWidget::bookingButtonClicked(){
    _stackedWindows->setCurrentIndex(1);
}
