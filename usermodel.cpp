#include "usermodel.h"

UserModel::UserModel(QObject *parent):QAbstractItemModel(parent)
{}

UserModel::UserModel(User user, QObject *parent):QAbstractItemModel(parent)
{
    this->_users.push_back(user);
}

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
                return user._address;
            case 4:
                return user._email;
            case 5:
                return user._age;
            case 6:
                return user._resortNumber;
            case 7:
             return user._isMale;
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
        _users.insert(position, {  int(),
                                   QString(),
                                   QByteArray(),
                                   QString(),
                                   QString(),
                                   short(),
                                   int(),
                                   bool()});

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
            case 0: user._accountID = value.toInt(); break;
            case 1: user._userName = value.toString(); break;
            case 2: user._passwordHash = value.toByteArray(); break;
            case 3: user._address = value.toString(); break;
            case 4: user._email = value.toString(); break;
            case 5: user._age = value.toInt();
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
