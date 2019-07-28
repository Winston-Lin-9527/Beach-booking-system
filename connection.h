#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>

static void createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // using default connection
    db.setDatabaseName("bookingDatabase.qsqlite");  // no subfix .db will create a new database file but will not work with existing file

    QFileInfo check_file("bookingDatabase.qsqlite");
        // check if file exists and if yes: Is it really a file and no directory?
        if (check_file.exists() && check_file.isFile()) {
            if (!db.open()) {
                QMessageBox::critical(nullptr, QObject::tr("Cannot open booking database"),
                QObject::tr("Unable to establish a database connection.\n"), QMessageBox::Cancel);
            }

        } else {
            // only called when no such file exist
            qDebug()<< "Database directory not found, now creating new database file";
            QSqlQuery query(db);
            query.prepare("CREATE TABLE bookings (id int primary key, customerID varchar(6), productID int, startTime varchar(10), duration30mins int)");

            if(!query.exec())
                qDebug() <<"Failed to create new database table";

            query.prepare("INSERT INTO bookings VALUES(?, ?, ?, ?, ?)");
            query.addBindValue(12);
            query.addBindValue("696969");
            query.addBindValue(8);
            query.addBindValue("kmkmkm");
            query.addBindValue(1);

            if(!query.exec())
                qDebug() << query.lastError();
        }

        QString ptrStr = QString("0x%1").arg((quintptr)&db, QT_POINTER_SIZE * 2, 16, QChar('0'));
        qDebug()<< "created default database: " << ptrStr;
}

static void destroyConnection(){
    // not needed because removeDatabase contains close()
    QSqlDatabase::removeDatabase(QSqlDatabase::database().databaseName());
}

#endif // CONNECTION_H
