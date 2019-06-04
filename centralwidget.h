#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include "usermodel.h"
#include "logindialog.h"

class CreateAccountWizard;
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

public slots:
    void createAccountButtonClicked();
    void bookingButtonClicked();
    void addAccount(User &user);

//    void editAccount();
//    void removeAccount();

private:
    QLabel *_welcomeLabel;
    QPushButton *_bookingButton;
    QPushButton *_createAccountButton;
    QPushButton *_loginAccountButton;

    QLayout *_mainLayout;
    QStackedWidget *_stackedWindows;
    QWidget *_introPageObject;
    QWidget *_bookingPageObject;

    QHBoxLayout *_introLayout;
    QGridLayout *_bookingLayout;

    CreateAccountWizard *_createAccountWizard;
    loginDialog *_loginDialog;

    UserModel *_userModel;
};

#endif // CENTRALWIDGET_H
