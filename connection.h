#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // using default connection
    db.setDatabaseName("bookingDatabase.db");
//    db.setUserName("Stranger things season 3");
//    db.setPassword("sucks!");

    if (!db.open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open booking database"),
            QObject::tr("Unable to establish a database connection.\n"), QMessageBox::Cancel);
        return false;
    } 

    QSqlQuery query(db);
    QString create_table("CREATE TABLE bookings (id int primary key, "
               "customerID varchar(6), productID int, startTime varchar(10), endTime varchar(10), duration30mins int)");
    query.prepare(create_table);

    if(!query.exec()){
        qDebug() << "error: can't creating table in bookings database.";
    }

//    query.exec("insert into person values(101, 'Danny', 'Young')");
//    query.exec("insert into person values(102, 'Christine', 'Holand')");
//    query.exec("insert into person values(103, 'Lars', 'Gordon')");
//    query.exec("insert into person values(104, 'Roberto', 'Robitaille')");
//    query.exec("insert into person values(105, 'Maria', 'Papadopoulos')");

//    query.exec("create table items (id int primary key,"
//                                             "imagefile int,"
//                                             "itemtype varchar(20),"
//                                             "description varchar(100))");
//    query.exec("insert into items "
//               "values(0, 0, 'Qt',"
//               "'Qt is a full development framework with tools designed to "
//               "streamline the creation of stunning applications and  "
//               "amazing user interfaces for desktop, embedded and mobile "
//               "platforms.')");
//    query.exec("insert into items "
//               "values(1, 1, 'Qt Quick',"
//               "'Qt Quick is a collection of techniques designed to help "
//               "developers create intuitive, modern-looking, and fluid "
//               "user interfaces using a CSS & JavaScript like language.')");
//    query.exec("insert into items "
//               "values(2, 2, 'Qt Creator',"
//               "'Qt Creator is a powerful cross-platform integrated "
//               "development environment (IDE), including UI design tools "
//               "and on-device debugging.')");
//    query.exec("insert into items "
//               "values(3, 3, 'Qt Project',"
//               "'The Qt Project governs the open source development of Qt, "
//               "allowing anyone wanting to contribute to join the effort "
//               "through a meritocratic structure of approvers and "
//               "maintainers.')");

    return true;
}

static void destroyConnection(){
    // may not need for closing database, we'll see
//    QSqlDatabase db = QSqlDatabase::database();
//    db.close();

    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

#endif // CONNECTION_H
