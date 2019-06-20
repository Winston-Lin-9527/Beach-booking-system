#ifndef USERMODEL_H
#define USERMODEL_H

#include <QString>
#include <QAbstractItemModel>
#include <QList>
#include <QDate>
#include <QTextStream>

struct User{
    QString _accountID;         //1
    QString _userName;          //2
    QByteArray _passwordHash;   //3
    QString _firstName;         //4
    QString _lastName;          //5
    QString _address;           //6
    QString _email;             //7
    int _resortNumber;          //8
    bool _isMale;               //9
    QDate _DOB;                 //10
    QString _visaNumber;        //11
    QDate _visaExpiryDate;      //12
    QString _CVV;               //13        *13 fields

    int operator== (const User &other) const {
        if((_userName == other._userName) || (_email == other._email))
            return 0;    // accountID and username and email subject to duplicate
            // need to make this returns the different cases, duplicate username or duplicate email or duplicate visa...etc
        }
    // bool operator overloaded as non-member to check if another User object is equal to this one
};

// overload these two operators ( << and >> ) to help format input and output of an User object's fields
//QDataStream &operator<< (QDataStream &out, User &user){
//       out << user._accountID;
//       out << user._userName;
//       out << user._passwordHash;
//       out << user._firstName;
//       out << user._lastName;
//       out << user._address;
//       out << user._email;
//       out << user._resortNumber;
//       out << user._isMale;
//       out << user._DOB;
//       out << user._visaNumber;
//       out << user._visaExpiryDate;
//       out << user._CVV;

//       return out;
//}

//QDataStream &operator>> (QDataStream &in, User &user){
//    in >> user._accountID;
//    in << user._userName;
//    in << user._passwordHash;
//    in << user._firstName;
//    in << user._lastName;
//    in << user._address;
//    in << user._email;
//    in << user._resortNumber;
//    in << user._isMale;
//    in << user._DOB;
//    in << user._visaNumber;
//    in << user._visaExpiryDate;
//    in << user._CVV;

//    return in;
//}

//QDataStream &operator<< (QDataStream &out, QList<User> &users){
//    for(int i = 0; i < users.size(); i++){
//            User user = users.at(i);
//            out << user;
//    }
//    return out;
//}

//QDataStream &operator>> (QDataStream &in, QList<User> &users){
//    for(int i = 0; i < users.size(); i++)
//        {
//            User user;
//            in >> user;
//            users.push_back(user);
//        }

//        return in;
//}

class UserModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    UserModel(QObject *parent);

    virtual int rowCount(const QModelIndex &parent)const override;
    virtual int columnCount(const QModelIndex &parent)const override;
    virtual QVariant data(const QModelIndex &index, int role)const override;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex &index) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    QList<User> getUsers() const;

private:
    QList<User> _users;
};

#endif // USERMODEL_H
