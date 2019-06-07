#include <QLabel>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>

#include "centralwidget.h"
#include "createaccountwizard.h"
#include "usermodel.h"

CentralWidget::CentralWidget(QWidget *parent)
{
    // key objects
    _stackedWindows = new QStackedWidget;
    _userModel = new UserModel(this);

    // dialogs
    _createAccountWizard = new CreateAccountWizard;
    _loginDialog = new loginDialog;

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
    connect(_loginDialog, SIGNAL(sendLoginCredentials(QString, QString)), this, SLOT(loginRequested(QString, QString)));
}

CentralWidget::~CentralWidget(){}

void CentralWidget::createAccountButtonClicked(){
    this->_createAccountWizard->restart();
    this->_createAccountWizard->exec();
}

void CentralWidget::bookingButtonClicked(){
    _stackedWindows->setCurrentIndex(1);
}

void CentralWidget::addAccount(User &newUserObject){
    if(!this->_userModel->getUsers().contains(newUserObject)){   // uses overrided operator '=' in User struct here
        // parameters: insert row before 0, add 13 rows, parent model index of the new row, in this case empty with no children,
        // by Qt documentation a single column of (second parameter) rows will be added
        this->_userModel->insertRows(0, 13, QModelIndex());

        // only the _accountID field, or the primary key, has to be handled differently because it is determined by cen
        newUserObject._accountID = this->genAccountID();

        // this is done quite primitively, but there's nothing wrong, even more efficient than an extra loop! LMAOooo
        QModelIndex index = this->_userModel->index(0, 0, QModelIndex());
        this->_userModel->setData(index, newUserObject._accountID);

        index = _userModel->index(0, 1, QModelIndex());
        this->_userModel->setData(index, newUserObject._userName);

        index = _userModel->index(0, 2, QModelIndex());
        this->_userModel->setData(index, newUserObject._passwordHash);  // need to convert to hash not plain text

        index = _userModel->index(0, 3, QModelIndex());
        this->_userModel->setData(index, newUserObject._firstName);

        index = _userModel->index(0, 4, QModelIndex());
        this->_userModel->setData(index, newUserObject._lastName);

        index = _userModel->index(0, 5, QModelIndex());
        this->_userModel->setData(index, newUserObject._address);

        index = _userModel->index(0, 6, QModelIndex());
        this->_userModel->setData(index, newUserObject._email);

        index = _userModel->index(0, 7, QModelIndex());
        this->_userModel->setData(index, newUserObject._resortNumber);

        index = _userModel->index(0, 8, QModelIndex());
        this->_userModel->setData(index, newUserObject._isMale);

        index = _userModel->index(0, 9, QModelIndex());
        this->_userModel->setData(index, newUserObject._DOB);

        index = _userModel->index(0, 10, QModelIndex());
        this->_userModel->setData(index, newUserObject._visaNumber);

        index = _userModel->index(0, 11, QModelIndex());
        this->_userModel->setData(index, newUserObject._visaExpiryDate);

        index = _userModel->index(0, 12, QModelIndex());
        this->_userModel->setData(index, newUserObject._CVV);

        qDebug() << "addAccount() called, first field: "<< newUserObject._CVV;
    }
    else{
        QMessageBox::information(this, QString("Duplicate"),
                   tr("The name \"%1\" already exists.").arg(newUserObject._userName));
    }

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


//    // the reason for converting into a set is because QSet is a hash table underneath, only allow unique elements,
//    // QSet::fromList auto filters the duplicates
//    QSet<User> userHashSet = QSet<User>::fromList(this->_userModel->getUsers());

