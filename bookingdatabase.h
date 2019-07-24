#ifndef BOOKINGDATABASE_H
#define BOOKINGDATABASE_H

#include <QTime>
#include <usermodel.h>

struct Booking{
    QString ID;
    QString customerID;
    int productID;
    QTime startTime;
    QTime endTime;
    bool duration30mins;    // if true 30 mins, if false 60 mins
};

/*
 * this class manipulates the booking database
 */

class BookingDatabase
{
public:
    BookingDatabase();

    void insertEntry(Booking bookingObject);
    void removeEntry(int id);
    bool retrieveEntry(QString customerID, QList<Booking> *entries);

private:
    QList <Booking> _bookingRecord;
};

#endif // BOOKINGDATABASE_H
