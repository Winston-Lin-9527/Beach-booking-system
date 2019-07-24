#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QList>

#include "bookingdatabase.h"

BookingDatabase::BookingDatabase()
{

}

void BookingDatabase::insertEntry(Booking bookingObject){
    QSqlQuery query(QSqlDatabase::database());

    QString query_insert("INSERT INTO bookings (id, customerID, productID, startTime, endTime, duration30mins"
                             "VALUES (:id, :customerID, :productID, :startTime, :endTime, :duration30mins)");
    query.prepare(query_insert);
    query.bindValue(":id", bookingObject.ID);
    query.bindValue(":customerID", bookingObject.customerID);
    query.bindValue(":productID", bookingObject.productID);
    query.bindValue(":startTime", bookingObject.startTime.toString("H:m:s"));
    query.bindValue(":endTime", bookingObject.endTime.toString("H:m:s"));
    query.bindValue(":duration30mins", (bookingObject.duration30mins == true) ? 1 : 0);

    if(!query.exec()){
        qDebug() << "error: failed to insert booking with productID: " << bookingObject.productID;
        qDebug() << query.lastError();
    }
}

void BookingDatabase::removeEntry(int id){
    QSqlQuery query(QSqlDatabase::database());

    QString query_remove("DELETE FROM student WHERE id = " + QString(id));
    query.prepare(query_remove);

    if(!query.exec()){
        qDebug() << "error: failed to remove entry.";
        qDebug() << query.lastError();
    }
}

/*
 *  the second parameter 'entries' is used to transfer the entry retrievals using pass by reference
 */

bool BookingDatabase::retrieveEntry(QString customerID, QList<Booking> *entries){
    QSqlQuery query(QSqlDatabase::database());

    QString query_findUser = QString("SELECT * FROM bookings WHERE customerID ='%1'").arg(customerID);
    query.prepare(query_findUser);

    if(!query.exec()){
        qDebug() << query.lastError();
    }

    QList<Booking> *loadedEntries = {};

    while(query.next()){
        loadedEntries->insert(-1, Booking{query.value(0).toString(),
                           query.value(1).toString(),
                           query.value(2).toInt(),
                           QTime::fromString(query.value(3).toString(), "H:m:s"),
                           QTime::fromString(query.value(4).toString(), "H:m:s"),
                           query.value(5).toBool()});
    }

    if(loadedEntries->size() == 0)
        return false;                // return false, don't do anything if no such entry exist at all


    entries = loadedEntries;     // assign the address of loadedEntries to parameter entries

   /*
    * # notes
    * To prefix the value with zeros, the fourth parameter needs to be QChar('0').
    * To output the correct number of digits, QT_POINTER_SIZE needs to be doubled (because each byte needs 2 hex digits).
    *  4 bits is one nibble and one hexadecimal digit
    */
    qDebug() << "BookingDatabase::retrieve: the address of entries is " + QString("0x%1").arg((quintptr)entries,
                                                                                              QT_POINTER_SIZE * 2, 16, QChar('0'));
    return true;
}
