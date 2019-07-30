#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include "usermodel.h"
#include "bookingwindow.h"

#include <QWidget>
#include <QCryptographicHash>

class CreateAccountWizard;
class LoginDialog;
class MyAccountPage;
class QLabel;
class QStackedWidget;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;

class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    CentralWidget(QWidget *parent = 0);
    virtual ~CentralWidget();

    QString genAccountID() const;
    QByteArray toHash(QString stringToHash, QCryptographicHash::Algorithm) const;   // hash the password

    void saveToFile();
    void loadFromFile();

public slots:
    void loginButtonClicked();
    void createAccountButtonClicked();
    void bookingButtonClicked();
    void backToHomePage();
    void logoutButtonClicked();

    void addAccount(User &user);
    void loginRequested(QString username, QString passwordInPlainText);
    void changeBalance(int newBalance);

private:
    QLabel *_welcomeLabel;
    QLabel *_welcomeLabelBanner;

    QPushButton *_bookingButton;
    QPushButton *_createAccountButton;
    QPushButton *_loginAccountButton;
    QPushButton *_logoutAccountButton;

    QLayout *_mainLayout;
    QStackedWidget *_stackedWindows;
    QWidget *_introPageObject;
    QWidget *_bookingPageObject;

    BookingWindow *_bookingWindow;

    QVBoxLayout *_introLayout;
    QHBoxLayout *_bookingLayout;

    CreateAccountWizard *_createAccountWizard;
    LoginDialog *_loginDialog;
    MyAccountPage *_myAccountPage;

    UserModel *_userModel;
    bool _isCurrentlyLogin;
    QString _userFileDirectory;
    User _currentUser;
    int shame;
};

#endif // CENTRALWIDGET_H
