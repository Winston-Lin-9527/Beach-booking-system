#include "usermodel.h"

UserModel::UserModel(QObject *parent):QAbstractItemModel(parent)
{}

UserModel::UserModel(User user, QObject *parent):QAbstractItemModel(parent)
{
    this->_users.push_back(user);
}

int UserModel::rowCount(const QModelIndex &index) const{
    return this->_users.size();
}

int UserModel::columnCount(const QModelIndex &index) const{
    return 8;   // the number of fields in one user object
}


