#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QTime>
#include <QTextStream>

struct Booking{
    QString ID;
    QString customerID;
    int productID;
    QDate date;
    QTime startTime;
    bool duration30mins;    // if true 30 mins, if false 60 mins
    int quantity;
};

inline QTextStream &operator<< (QTextStream &out, Booking &booking){
       out << booking.ID<<endl;
       out << booking.customerID<<endl;
       out << booking.productID<<endl;
       out << booking.date.toString("yyyy.MM.dd")<<endl;
       out << booking.startTime.toString("H:m:s")<<endl;
       out << booking.duration30mins<<endl;
       out << booking.quantity<<endl;
       return out;
}

inline QTextStream &operator>> (QTextStream &in, Booking *booking){
    QString temp;

    in >> booking->ID;
    in >> booking->customerID;
    in >> booking->productID;
    in >> temp;
    booking->date = QDate::fromString(temp, "yyyy.MM.dd");
    in >> temp;
    booking->startTime = QTime::fromString(temp, "H:m:s");
    in >> temp;
    booking->duration30mins = temp == "1" ? true : false;
    in >> booking->quantity;

    return in;
}

inline QTextStream &operator<< (QTextStream &out, const QList<Booking> &bookings){
    out << bookings.size() << endl;    // this is an index used to record the number of user saved

    for(int i = 0; i < bookings.size(); i++){
            Booking booking = bookings.at(i);
            out << booking;
    }
    return out;
}

inline QTextStream &operator>> (QTextStream &in, QList<Booking> *bookings){
    int count = 0;
    in >> count;        // records how the number of users, works alongside with first line in operator <<

    for(int i = 0; i < count; i++){
            Booking *booking = new Booking;
            in >> booking;
            bookings->push_back(*booking);
    }
    return in;
}

class databasehandler
{
public:
    databasehandler();

    void saveToFile();
    void loadFromFile();

    bool checkTimeCollision(Booking newBooking);

    void addBooking(Booking newBooking);

    QList<Booking> getBookings() const;

private:
    QList<Booking> _bookings;
};

#endif // DATABASEHANDLER_H
