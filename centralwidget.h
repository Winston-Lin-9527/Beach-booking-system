#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>
#include <usermodel.h>

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

private:
    QLabel *_label;
    QLabel *_label2;

    QStackedWidget *_stackedWindows;
    QPushButton *_bookingButton;
    QPushButton *_createAccountButton;

    CreateAccountWizard *_createAccountWizard;

    UserModel *_userModel;
};

#endif // CENTRALWIDGET_H
