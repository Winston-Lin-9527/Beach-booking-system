#include <QFile>
#include <QMessageBox>
#include <QDebug>

#include "databasehandler.h"

databasehandler::databasehandler()
{

}

void databasehandler::saveToFile(){
    QFile file("database.sqlite");

    if (!file.open(QIODevice::WriteOnly)) {
            qDebug()<<"error writing from file";
            return;
        }

        QTextStream outStream(&file);
        outStream<<_bookings;

        qDebug() << "database written to file.";

        file.close();
}

void databasehandler::loadFromFile(){
//    QString fileName = QFileDialog::getSaveFileName(this,
//           tr("Save Address Book"), "",
//           tr("Address Book (*.abk);;All Files (*)"));

    QFile file("database.sqlite");

       if (!file.open(QIODevice::ReadOnly)) {
           qDebug()<<"error loading from file";
           return;
       }

       QTextStream inStream(&file);
       inStream >> &_bookings;

       file.close();
}

bool databasehandler::checkTimeCollision(Booking newBooking){
    bool collided = false;
//    if(newBooking.duration30mins)

//    // check if any time product with time range collision
//    for(int i=0; i<_bookings.size(); i++){
//        if(_bookings.at(i).customerID == newBooking.customerID)
//            if(_bookings.at(i).startTime.secsTo(newBooking.startTime) < 0 || this->_timeEdit->time().secsTo(loadedEntries.at(i).endTime) > 0)
//                 collided = true;
//    }

    return collided;
}

QList<Booking> databasehandler::getBookings() const{
    return this->_bookings;
}

void databasehandler::addBooking(Booking booking){
    this->_bookings.append(booking);
}
