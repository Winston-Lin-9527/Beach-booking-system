#ifndef MYACCOUNTPAGE_H
#define MYACCOUNTPAGE_H

#include <QDialog>

class QLabel;
class QTableWidget;
class QGridLayout;

class MyAccountPage : public QDialog
{
    Q_OBJECT

public:
    MyAccountPage();
    MyAccountPage(QString accountID);
    void openPage();

private:
    QTableWidget *_bookingRecordTable;
    QLabel *_activeBookingLabel;
    QLabel *_accountAboutLabel;

    QString *_accountID;

    QGridLayout *_mLayout;
};

#endif // MYACCOUNTPAGE_H
