#ifndef MYACCOUNTPAGE_H
#define MYACCOUNTPAGE_H

#include <QDialog>

#include "usermodel.h"

class QLabel;
class QTableWidget;
class QGridLayout;

class MyAccountPage : public QDialog
{
    Q_OBJECT

public:
    MyAccountPage();
    void openPage(QString customerID, int balance);

private:
    QTableWidget *_bookingRecordTable;
    QLabel *_activeBookingLabel;
    QLabel *_accountAboutLabel;
    QLabel *_balanceLabel;

    QGridLayout *_mLayout;
};

#endif // MYACCOUNTPAGE_H
