#include <QLabel>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

#include "centralwidget.h"
#include "createaccountwizard.h"
#include "logindialog.h"
#include "myaccountpage.h"
#include "usermodel.h"

CentralWidget::CentralWidget(QWidget *parent)
{
    // key objects
    _stackedWindows = new QStackedWidget;
    _userModel = new UserModel(this);
    _isCurrentlyLogin = false;
    _currentSessionUserID = "";
    _userFileDirectory = "userBase.sqlite";    // by default the file storing is userBase.txt, but customization is ok

    // dialogs
    _createAccountWizard = new CreateAccountWizard;
    _loginDialog = new LoginDialog;

    // layouts structures
    _mainLayout = new QHBoxLayout(this);
    _introLayout = new QVBoxLayout(this);
    _bookingLayout = new QHBoxLayout(this);

    _introPageObject = new QWidget(this);
    _bookingPageObject = new QWidget(this);

    // elements in the first page
    _welcomeLabel = new QLabel("Welcome To The Beach Sport Renting System");
    QFont font;
    font.setBold(true);
    font.setPointSize(25);
    _welcomeLabel->setFont(font);

    _welcomeLabelBanner = new QLabel;
    QImage bannerImage(":/resources/images/mainBanner.jpg");
    QPixmap bannerPixmap = QPixmap::fromImage(bannerImage);
    QPixmap processedPixmap = bannerPixmap.scaled(_welcomeLabel->size(), Qt::KeepAspectRatio);
    _welcomeLabelBanner->setPixmap(processedPixmap);

    QVBoxLayout *welcomeLayout = new QVBoxLayout;
    welcomeLayout->addWidget(_welcomeLabel);
    welcomeLayout->addWidget(_welcomeLabelBanner);
    welcomeLayout->setContentsMargins(0, 5, 0, 80);

    _createAccountButton = new QPushButton("create account");
    _bookingButton = new QPushButton("Make New Bookings");
    _loginAccountButton = new QPushButton("Login");

    // booking page
    _bookingWindow = new BookingWindow();

    // first page
    this->_introLayout->setMargin(5);
    _introLayout->addLayout(welcomeLayout);
    _introLayout->addWidget(_loginAccountButton);
    _introLayout->addWidget(_bookingButton);
    _introLayout->addWidget(_createAccountButton);
    _introPageObject->setLayout(_introLayout);

    // second page
    this->_bookingLayout = new QHBoxLayout(this);
    _bookingLayout->setSpacing(10);
    _bookingLayout->addWidget(_bookingWindow);
    _bookingPageObject->setLayout(_bookingLayout);

    /*
     *  add pages to the stacked window widget
     */
    _stackedWindows->addWidget(_introPageObject);
    _stackedWindows->addWidget(_bookingPageObject);

    _mainLayout->addWidget(_stackedWindows);
    setLayout(_mainLayout);

    loadFromFile();

    connect(_createAccountButton, SIGNAL(clicked()), this, SLOT(createAccountButtonClicked()));
    connect(_bookingButton, SIGNAL(clicked()), this, SLOT(bookingButtonClicked()));
    connect(_createAccountWizard->page(4), SIGNAL(sendDetails(User&)), this, SLOT(addAccount(User&)));
    connect(_loginAccountButton, SIGNAL(clicked()), this, SLOT(loginButtonClicked()));
    connect(_loginDialog, SIGNAL(requestLogin(QString, QString)), this, SLOT(loginRequested(QString, QString)));
    connect(_bookingWindow, SIGNAL(signalBackToHomePage()), this, SLOT(backToHomePage()));
}

CentralWidget::~CentralWidget(){}

void CentralWidget::loginButtonClicked(){
    if(this->_isCurrentlyLogin == false)
        this->_loginDialog->open(); // apparently better than exec() ?...
    else{
        this->_myAccountPage = new MyAccountPage(this->_currentSessionUserID);
        _myAccountPage->openPage();
    }
}

void CentralWidget::createAccountButtonClicked(){
    this->_createAccountWizard->restart();
    this->_createAccountWizard->exec();
}

void CentralWidget::bookingButtonClicked(){
    if(this->_isCurrentlyLogin){
        _stackedWindows->setCurrentIndex(1);
        _bookingWindow->setCustomerID(_currentSessionUserID);
    }
    else
        QMessageBox::information(this, "Warning", "Please login first.");
}

void CentralWidget::backToHomePage(){
    _stackedWindows->setCurrentIndex(0);
}

void CentralWidget::addAccount(User &newUserObject){
    if(!this->_userModel->getUsers().contains(newUserObject)){   // uses overrided operator '=' in User struct here
        // parameters: insert 1 rows before existing, parent model index of the new row, in this case empty with no children,
        // by Qt documentation a single column of (second parameter) rows will be added
        this->_userModel->insertRows(0, 1, QModelIndex());

        // only the _accountID field, or the primary key, has to be handled differently because it is determined by cen
        newUserObject._accountID = this->genAccountID();

        // hash the password, and store in hash only, even the admins don't know the passwords.
        // therefore prevent password breach, protects user and system security
        // also use SHA256, very secure encryption algorithm
        newUserObject._passwordHash = toHash(newUserObject._passwordHash, QCryptographicHash::Sha256);

        // this is done quite primitively, but there's nothing wrong, even more efficient than an extra loop! LMAOooo
        QModelIndex index = this->_userModel->index(0, 0, QModelIndex());
        this->_userModel->setData(index, newUserObject._accountID);

        index = _userModel->index(0, 1, QModelIndex());
        this->_userModel->setData(index, newUserObject._userName);

        index = _userModel->index(0, 2, QModelIndex());
        this->_userModel->setData(index, newUserObject._passwordHash);

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
    }
    else{
        QMessageBox::information(this, QString("Duplicate"),
                   tr("The name \"%1\" already exists.").arg(newUserObject._userName));
    }
    qDebug() << "now there are "<< _userModel->getUsers().size() << " users in database";
    saveToFile();
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

QByteArray CentralWidget::toHash(QString stringToHash, QCryptographicHash::Algorithm algorithm) const{
    QCryptographicHash cryptoObject(algorithm);
    cryptoObject.addData(stringToHash.toLatin1());    // alternative QString::toUTF8 toLocal8Bit

    return cryptoObject.result().toHex();
}

void CentralWidget::loginRequested(QString username, QString passwordInPlainText){
    QByteArray passwordInHash = this->toHash(passwordInPlainText, QCryptographicHash::Sha256);
    qDebug() << "login requested";
    QModelIndex index = QModelIndex();
    bool found = false;
    index = this->_userModel->index(0, 2, QModelIndex());

    for(int row = 0; row < this->_userModel->getUsers().size(); row++){
         index = this->_userModel->index(row, 1, QModelIndex());
         qDebug() << "follow user: " << this->_userModel->data(index, Qt::DisplayRole);
         if(username == this->_userModel->data(index, Qt::DisplayRole)){
             found = true;
             // if user exists then check the password
             index = this->_userModel->index(row, 2, QModelIndex());

             if(passwordInHash == this->_userModel->data(index, Qt::DisplayRole).toByteArray()){
                  // the credentials are now verified.
                 qDebug() << "login successful";
                 this->_loginAccountButton->setText("View My Account");

                 index = this->_userModel->index(row, 0, QModelIndex());
                 this->_currentSessionUserID = this->_userModel->data(index, Qt::DisplayRole).toString();

                 this->_loginDialog->handleReturnStatus(StatusCode::LOGIN_SUCCESS);
                 this->_isCurrentlyLogin = true;
             }
             else{
                 this->_loginDialog->handleReturnStatus(StatusCode::LOGIN_FAILURE_NONMATCHING_CREDENTIALS);
                 qDebug() << "Login failure: username and password don't match! ";
             }
         }
    }
    if(!found){
        this->_loginDialog->handleReturnStatus(StatusCode::LOGIN_FAILURE_NON_EXIST_USER);
        qDebug() << "login failure: username " << username << " doesn't exist";
    }
}

/*
 *  the logics behind saveToFile() and loadFromFile() are back in userModel.h, which makes these two look clean.
 */
void CentralWidget::saveToFile(){
    QFile file(this->_userFileDirectory);

    if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }

        QTextStream outStream(&file);
        outStream<<this->_userModel->getUsers();

        qDebug() << "database written to file.";

        file.close();
}

void CentralWidget::loadFromFile(){
    QFile file(this->_userFileDirectory);

       if (!file.open(QIODevice::ReadWrite)) {
           QMessageBox::information(this, tr("Warning"),
               "Couldn't find database in directory, now creating new one.");
           return;
       }

       QTextStream inStream(&file);
       inStream >> _userModel->getUsersAddress();

       file.close();
}
