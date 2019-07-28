#ifndef BOOKINGDATABASEUTILS_H
#define BOOKINGDATABASEUTILS_H

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
 * this class provides a layer of interface to manipulate the booking database
 */

class BookingDatabaseUtils
{
public:
    BookingDatabaseUtils();

    static void insertEntry(Booking bookingObject);
    static void removeEntry(int id);
    static QList<Booking> retrieveEntry(QString customerID);

private:
    QList <Booking> _bookingRecord;
};

#endif // BOOKINGDATABASEUTILS_H
