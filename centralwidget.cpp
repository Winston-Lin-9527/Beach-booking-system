#include <QLabel>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QDialog>
#include <QDebug>

#include "centralwidget.h"
#include "createaccountwizard.h"
#include "usermodel.h"

CentralWidget::CentralWidget(QWidget *parent)
{
    _stackedWindows = new QStackedWidget;
    _createAccountWizard = new CreateAccountWizard;
    _loginDialog = new loginDialog;
    _userModel = new UserModel(this);

    // layouts structures
    _mainLayout = new QHBoxLayout(this);
    _introLayout = new QHBoxLayout(this);
    _bookingLayout = new QGridLayout(this);

    _introPageObject = new QWidget(this);
    _bookingPageObject = new QWidget(this);

    // elements of the first page
    _welcomeLabel = new QLabel("this is the beach sport renting system");

    _createAccountButton = new QPushButton("create account");
    _bookingButton = new QPushButton("Make New Bookings");
    _loginAccountButton = new QPushButton("Login");

    // elements of the booking page
    QLabel *label2 = new QLabel("ddd");

    // first page
    this->_introLayout->setMargin(5);
    _introLayout->addWidget(_welcomeLabel);
    _introLayout->addWidget(_createAccountButton);
    _introLayout->addWidget(_bookingButton);
    _introLayout->addWidget(_loginAccountButton);
    _introPageObject->setLayout(_introLayout);

    // second page
    this->_bookingLayout = new QGridLayout(this);
    _bookingLayout->setSpacing(10);
    _bookingLayout->addWidget(label2, 0, 0);
    _bookingPageObject->setLayout(_bookingLayout);

    /*
     *  add pages to the stacked window widget
     */
    _stackedWindows->addWidget(_introPageObject);
    _stackedWindows->addWidget(_bookingPageObject);

    _mainLayout->addWidget(_stackedWindows);
    setLayout(_mainLayout);

    connect(_createAccountButton, SIGNAL(clicked()), this, SLOT(createAccountButtonClicked()));
    connect(_bookingButton, SIGNAL(clicked()), this, SLOT(bookingButtonClicked()));
    connect(_createAccountWizard->page(4), SIGNAL(sendDetails(User&)), this, SLOT(addAccount(User&)));
    connect(_loginAccountButton, SIGNAL(clicked()), _loginDialog, SLOT(exec()));
}

CentralWidget::~CentralWidget(){}

void CentralWidget::createAccountButtonClicked(){
    this->_createAccountWizard->restart();
    this->_createAccountWizard->exec();
}

void CentralWidget::bookingButtonClicked(){
    _stackedWindows->setCurrentIndex(1);
}

void CentralWidget::addAccount(User &user){
    // genAccountID() then add to userModel
}

QString CentralWidget::genAccountID() const{
    srand(time(NULL));

    int ID[6];

    for (int i=0; i<6; ++i)
        ID[i] = rand() % 10;

        char s[6] = {0};
        int n = 0;

        for (int i = 0; i < 6; i++) {
            n += sprintf(&s[n], "%d", ID[i]);
        }

    return QString(s);
}
