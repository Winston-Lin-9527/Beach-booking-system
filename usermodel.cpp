#include <QDate>

#include "usermodel.h"


UserModel::UserModel(QObject *parent):QAbstractItemModel(parent){ }

int UserModel::rowCount(const QModelIndex &index) const{
    Q_UNUSED(index)

    return this->_users.size();
}

int UserModel::columnCount(const QModelIndex &index) const{
    Q_UNUSED(index)

    return 8;   // the number of fields in one user object
}

QVariant UserModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid())
        return QVariant();

    if(index.row() >= _users.size() || index.row() < 0)
        return QVariant();

    if(role == Qt::DisplayRole){
        const User &user  = _users.at(index.row());

        switch(index.column()){
            case 0:
                return user._accountID;
            case 1:
                return user._userName;
            case 2:
                return user._passwordHash;
            case 3:
                return user._firstName;
            case 4:
                return user._lastName;
            case 5:
                return user._address;
            case 6:
                return user._email;
            case 7:
                return user._resortNumber;
            case 8:
                return user._isMale;
            case 9:
                return user._DOB;
            case 10:
                return user._visaNumber;
            case 11:
                return user._visaExpiryDate;
            case 12:
                return user._CVV;
        }
    }
    return QVariant();
}

QModelIndex UserModel::index(int row, int column, const QModelIndex &parent) const{
    return createIndex(row, column);
}

QModelIndex UserModel::parent(const QModelIndex &index) const{
    return QModelIndex();
}

/*  work on this function later
 */
QVariant UserModel::headerData(int section, Qt::Orientation orientation, int role) const{
    // use section later

    return QVariant();
}

bool UserModel::insertRows(int position, int rows, const QModelIndex &index){
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    Q_UNUSED(index)

    for(int row = 0; row < rows; ++row)
        _users.insert(position, {  QString(),
                                   QString(),
                                   QByteArray(),
                                   QString(),
                                   QString(),
                                   QString(),
                                   QString(),
                                   int(),
                                   bool(),
                                   QDate(),
                                   QString(),
                                   QDate(),
                                   QString()});
    endInsertRows();
    return true;
}

bool UserModel::removeRows(int position, int rows, const QModelIndex &index){
    beginRemoveRows(QModelIndex(), position, position + rows -1);

    for(int row = 0; row < rows; ++row)
        _users.removeAt(position);

    endRemoveRows();
    return true;
}

bool UserModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(index.isValid() && role == Qt::EditRole){    // actually don't need EditRole check...
        User user = _users.value(index.row());

        switch(index.column()){
            case 0: user._accountID = value.toString(); break;
            case 1: user._userName = value.toString(); break;
            case 2: user._passwordHash = value.toByteArray(); break;
            case 3: user._firstName = value.toString(); break;
            case 4: user._lastName = value.toString(); break;
            case 5: user._address = value.toString(); break;
            case 6: user._email = value.toString(); break;
            case 7: user._resortNumber = value.toInt(); break;
            case 8: user._isMale = value.toBool(); break;   // good thing to note this enum to bool logics is done in createAccountWizard
            case 9: user._DOB = value.toDate(); break;
            case 10: user._visaNumber = value.toString(); break;
            case 11: user._visaExpiryDate = value.toDate(); break;
            case 12: user._CVV = value.toString(); break;

            default: return false;
        }

        this->_users.replace(index.row(), user);
        emit dataChanged(index, index, {role});     // tell other views to update

        return true;
    }
    return false;   // if index not valid return false;
}

/*
 * this is an important function
 */
Qt::ItemFlags UserModel::flags(const QModelIndex &index) const{
    if(!index.isValid())
        return Qt::ItemIsEnabled;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

QList<User> UserModel::getUsers()const{
    return this->_users;
}

QList<User> *UserModel::getUsersAddress(){
    return &this->_users;
}
