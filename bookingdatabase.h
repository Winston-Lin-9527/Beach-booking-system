#ifndef BOOKINGDATABASE_H
#define BOOKINGDATABASE_H

#include <QTime>

struct BookingObject{
    QString ID;
    QString customerID;
    int productID;
    QTime startTime;
    QTime endTime;
    bool duration30mins;
};

class bookingDatabase
{
public:
    bookingDatabase();

private:
    QList <BookingObject> _bookingRecord;
};

#endif // BOOKINGDATABASE_H
