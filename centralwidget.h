#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

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
    void createAccountButtonClicked();
    void bookingButtonClicked();

private:
    QStackedWidget *_stackedWindows;
    QPushButton *_bookingButton;
    QPushButton *_createAccountButton;
    CreateAccountWizard *_createAccountWizard;
    QVBoxLayout *_createAccountWizardLayout;

    QLabel *_label;
    QLabel *_label2;
};

#endif // CENTRALWIDGET_H
