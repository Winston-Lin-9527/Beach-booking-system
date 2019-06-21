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
#include "usermodel.h"

CentralWidget::CentralWidget(QWidget *parent)
{
    // key objects
    _stackedWindows = new QStackedWidget;
    _userModel = new UserModel(this);
    _isCurrentlyLogin = false;
    _currentSessionUserID = "";
    _userFileDirectory = "userBase.txt";    // by default the file storing is userBase.txt, this allows for customization

    // dialogs
    _createAccountWizard = new CreateAccountWizard;
    _loginDialog = new LoginDialog;

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

    loadFromFile();

    connect(_createAccountButton, SIGNAL(clicked()), this, SLOT(createAccountButtonClicked()));
    connect(_bookingButton, SIGNAL(clicked()), this, SLOT(bookingButtonClicked()));
    connect(_createAccountWizard->page(4), SIGNAL(sendDetails(User&)), this, SLOT(addAccount(User&)));
    connect(_loginAccountButton, SIGNAL(clicked()), _loginDialog, SLOT(exec()));
    connect(_loginDialog, SIGNAL(requestLogin(QString, QString)), this, SLOT(loginRequested(QString, QString)));
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

   // if(!this->_userModel->getUsers().contains(newUserObject)){   // uses overrided operator '=' in User struct here
        // parameters: insert 1 rows before existing, parent model index of the new row, in this case empty with no children,
        // by Qt documentation a single column of (second parameter) rows will be added
        this->_userModel->insertRows(0, 1, QModelIndex());

        // only the _accountID field, or the primary key, has to be handled differently because it is determined by cen
        newUserObject._accountID = this->genAccountID();

        // hash the password, and store in hash only, even the admins don't know the passwords.
        // therefore prevent password breach, protects user and system security
        // also use SHA256, very secure encryption algorithm
        newUserObject._passwordHash = toHash(newUserObject._passwordHash, QCryptographicHash::Sha256);
        qDebug() << "passwordhash: " << newUserObject._passwordHash;

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
        qDebug() << "DOB before savetoFile: " << newUserObject._DOB;

        index = _userModel->index(0, 10, QModelIndex());
        this->_userModel->setData(index, newUserObject._visaNumber);

        index = _userModel->index(0, 11, QModelIndex());
        this->_userModel->setData(index, newUserObject._visaExpiryDate);

        index = _userModel->index(0, 12, QModelIndex());
        this->_userModel->setData(index, newUserObject._CVV);
//    }
//    else{
//        QMessageBox::information(this, QString("Duplicate"),
//                   tr("The name \"%1\" already exists.").arg(newUserObject._userName));
//    }
    qDebug() << "now there are "<< _userModel->getUsers().size() << " users ";
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
    qDebug() << "toHash() returns " << cryptoObject.result().toHex();
    return cryptoObject.result().toHex();
}

void CentralWidget::loginRequested(QString username, QString passwordInPlainText){

    QByteArray passwordInHash = this->toHash(passwordInPlainText, QCryptographicHash::Sha256);

    QModelIndex index = QModelIndex();
    bool found = false;
    index = this->_userModel->index(0, 2, QModelIndex());

    for(int row = 0; row < this->_userModel->getUsers().size(); row++){
         index = this->_userModel->index(row, 1, QModelIndex());
         if(username == this->_userModel->data(index, Qt::DisplayRole)){
             found = true;
             // if user exists then check the password
             index = this->_userModel->index(row, 2, QModelIndex());

             if(passwordInHash == this->_userModel->data(index, Qt::DisplayRole).toByteArray()){
                  // the credentials are now verified.
                 qDebug() << "login successful";

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

        file.close();
}

void CentralWidget::loadFromFile(){
//    QString fileName = QFileDialog::getSaveFileName(this,
//           tr("Save Address Book"), "",
//           tr("Address Book (*.abk);;All Files (*)"));

    QFile file(this->_userFileDirectory);

       if (!file.open(QIODevice::ReadOnly)) {
           QMessageBox::information(this, tr("Warning"),
               "Couldn't find database in directory, now creating new one.");
           return;
       }

       QTextStream inStream(&file);

       inStream >> _userModel->getUsersAddress();
       qDebug() << "Loaded database has size: " << _userModel->getUsers().size();
       qDebug() << "first loaded user has id: " << _userModel->getUsers().at(0)._accountID;
       qDebug() << "first loaded user has userName: " << _userModel->getUsers().at(0)._userName;
       qDebug() << "first loaded user has PasswordHash: " << _userModel->getUsers().at(0)._passwordHash;
       qDebug() << "first loaded user has firstname: " << _userModel->getUsers().at(0)._firstName;
       qDebug() << "first loaded user has lastname: " << _userModel->getUsers().at(0)._lastName;
       qDebug() << "first loaded user has dob: " << _userModel->getUsers().at(0)._DOB.toString("yyyy.MM.dd");
       qDebug() << "first loaded user has ismale: " << _userModel->getUsers().at(0)._isMale;

       // this is complete success
       file.close();
}
