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

    connect(_createAccountButton, SIGNAL(clicked()), this, SLOT(createAccountButtonClicked()));
    connect(_bookingButton, SIGNAL(clicked()), this, SLOT(bookingButtonClicked()));

//    connect(_createAccountWizard->page(5), SIGNAL(sendDetails(User &newUser)), this, SLOT(addAccount(User &newUser)));
}

CentralWidget::~CentralWidget(){}

void CentralWidget::createAccountButtonClicked(){
    this->_createAccountWizard->restart();
    this->_createAccountWizard->exec();
}

void CentralWidget::bookingButtonClicked(){
    _stackedWindows->setCurrentIndex(1);
}

void CentralWidget::addAccount(User &newUser){
    // usermodel add the userUser
}

//QString SummaryPage::createAccountID() const{
//    srand(time(NULL));

//    int ID[6];

//    for (int i=0; i<6; ++i)
//        ID[i] = rand() % 10;

//        char s[6] = {0};
//        int n = 0;

//        for (int i = 0; i < 6; i++) {
//            n += sprintf (&s[n], "%d", ID[i]);
//        }

//    return QString(s);
//}
