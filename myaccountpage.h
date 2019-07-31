#ifndef MYACCOUNTPAGE_H
#define MYACCOUNTPAGE_H

#include <QDialog>

#include "usermodel.h"

class QLabel;
class QTableWidget;
class QGridLayout;
class QSpinBox;
class QPushButton;

class MyAccountPage : public QDialog
{
    Q_OBJECT

public:
    MyAccountPage();
    void openPage(QString customerID, int balance);

signals:
    void balanceChanged(int newBalance);

private slots:
    void topupButtonClicked();

private:
    QTableWidget *_bookingRecordTable;
    QLabel *_activeBookingLabel;
    QLabel *_accountAboutLabel;
    QLabel *_balanceLabel;

    QLabel *_topupLabel;
    QPushButton *_topupButton;
    QSpinBox *_topupSpinBox;

    QGridLayout *_mLayout;

    int _balance;
};

#endif // MYACCOUNTPAGE_H
