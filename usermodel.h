#ifndef USERMODEL_H
#define USERMODEL_H

#include <QString>
#include <QAbstractItemModel>
#include <QList>
#include <QDate>

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

    int operator == (const User &other) const {
        if((_userName == other._userName) || (_email == other._email))
            return 0;    // accountID and username and email subject to duplicate
            // need to make this returns the different cases, duplicate username or duplicate email or duplicate visa...etc
        }
    // bool operator overloaded as non-member to check if another User object is equal to this one
};

class UserModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    UserModel(QObject *parent);
    UserModel(User user, QObject *parent);

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
