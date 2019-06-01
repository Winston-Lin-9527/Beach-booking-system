#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include "usermodel.h"

class CreateAccountWizard;
class QLabel;
class QStackedWidget;
class QPushButton;
class QVBoxLayout;

class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    CentralWidget(QWidget *parent = 0);
    virtual ~CentralWidget();

public slots:
    void bookingButtonClicked();
//    void addAccount(User &newUser);
//    void editAccount();
//    void removeAccount();

private:
    QLabel *_welcomeLabel;
    QPushButton *_bookingButton;
    QPushButton *_createAccountButton;

    QStackedWidget *_stackedWindows;
    QWidget *_mainPage;

    QLayout *_mainLayout;

    CreateAccountWizard *_createAccountWizard;

    UserModel *_userModel;
};

#endif // CENTRALWIDGET_H
