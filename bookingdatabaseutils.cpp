#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QList>

#include "bookingdatabaseutils.h"

BookingDatabaseUtils::BookingDatabaseUtils()
{

}

void BookingDatabaseUtils::insertEntry(Booking bookingObject){
    QSqlQuery query(QSqlDatabase::database("connection"));

    QString query_insert("INSERT INTO bookings (customerID, productID, startTime, duration30mins"
                             "VALUES (:customerID, :productID, :startTime, :duration30mins)");
    query.prepare(query_insert);
    query.bindValue(":customerID", bookingObject.customerID);
    query.bindValue(":productID", bookingObject.productID);
    query.bindValue(":startTime", bookingObject.startTime.toString("H:m:s"));
    query.bindValue(":duration30mins", (bookingObject.duration30mins == true) ? 1 : 0);

    if(!query.exec()){
        qDebug() << "error: failed to insert booking with productID: " << bookingObject.productID;
        qDebug() << query.lastError();
    }
}

void BookingDatabaseUtils::removeEntry(int id){
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

QList<Booking> BookingDatabaseUtils::retrieveEntry(QString customerID){
    QSqlDatabase db = QSqlDatabase::database();
    QString ptrStr = QString("0x%1").arg((quintptr)&db,
                        QT_POINTER_SIZE * 2, 16, QChar('0'));
    qDebug()<< "received default database: " << ptrStr;

    QSqlQuery query(db);

    QString query_findUser = QString("SELECT * FROM bookings WHERE customerID = 696969"); // change back to customerID todo
    query.prepare(query_findUser);

    if(!query.exec()){
        qDebug() << query.lastError();
    }

    qDebug() <<"first customerID: " <<query.first();

    QList<Booking> loadedEntries;

//    while(query.next()){
//        loadedEntries.insert(-1, Booking{
//                           query.value(0).toString(),
//                           query.value(1).toInt(),
//                           QTime::fromString(query.value(2).toString(), "H:m:s"),
                           
//                           query.value(3).toBool()});
//    }

   /* this is for historical rememberence of the blood and tears spilled on this battlegroung, been stupid.
    * # notes
    * To prefix the value with zeros, the fourth parameter needs to be QChar('0').
    * To output the correct number of digits, QT_POINTER_SIZE needs to be doubled (because each byte needs 2 hex digits).
    *  4 bits is one nibble and one hexadecimal digit
    */
//    qDebug() << "BookingDatabase::retrieve: the address of entries is " + QString("0x%1").arg((quintptr)entries,
//                                                                                              QT_POINTER_SIZE * 2, 16, QChar('0'));
    return loadedEntries;
}
