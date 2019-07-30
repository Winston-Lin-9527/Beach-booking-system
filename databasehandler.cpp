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
    QTime endTime;

    if(newBooking.duration30mins)
        endTime = newBooking.startTime.addSecs(1800);
    else
        endTime = newBooking.startTime.addSecs(3600);

//     qDebug()<<"New Start time: "<<newBooking.startTime;
//     qDebug()<<"New end time: "<<endTime;

//     qDebug()<<"Old start time: "<<_bookings.at(0).startTime;
//     QTime tempEndTime;
//     if(_bookings.at(0).duration30mins == true)
//         tempEndTime = _bookings.at(0).startTime.addSecs(1800);
//     else
//         tempEndTime = _bookings.at(0).startTime.addSecs(3600);
//     qDebug()<<"Old end time: "<<tempEndTime;

//     qDebug()<<"new start secs to old end: "<<_bookings.at(0).startTime.secsTo(endTime);


//    // check if any time product with time range collision
    for(int i=0; i<_bookings.size(); i++){
        if(_bookings.at(i).customerID == newBooking.customerID){
            qDebug()<<"Existing booking time: "<<_bookings.at(i).startTime;
            QTime tempEndTime;
            if(_bookings.at(i).duration30mins == true)
                tempEndTime = _bookings.at(i).startTime.addSecs(1800);
            else
                tempEndTime = _bookings.at(i).startTime.addSecs(3600);

            if((_bookings.at(i).date == newBooking.date))
                if((_bookings.at(i).startTime.secsTo(endTime) >= 0 && endTime.secsTo(tempEndTime) >= 0)
                        || (_bookings.at(i).startTime.secsTo(newBooking.startTime) >= 0 && newBooking.startTime.secsTo(tempEndTime) >= 0))
                    collided = true;
        }
    }
    return collided;
}

QList<Booking> databasehandler::getBookings() const{
    return this->_bookings;
}

void databasehandler::addBooking(Booking booking){
    this->_bookings.append(booking);
}
