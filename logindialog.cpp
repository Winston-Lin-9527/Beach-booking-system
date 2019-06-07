#include "logindialog.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QObject>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>

loginDialog::loginDialog() : QDialog()
{
    _buttonBox = new QDialogButtonBox();
    _buttonBox->addButton("Login", QDialogButtonBox::AcceptRole);
    _buttonBox->addButton("Cancel", QDialogButtonBox::RejectRole);

    _lineEditUsername = new QLineEdit;
    _lineEditPassword = new QLineEdit;

    _lineEditUsername->setPlaceholderText("");
    _lineEditPassword->setPlaceholderText("");

    _lineEditUsernameLabel = new QLabel("Username:");
    _lineEditPasswordLabel = new QLabel("Password");

    _mainLayout = new QVBoxLayout;

    QHBoxLayout *usernameLineEditLayout = new QHBoxLayout;
    usernameLineEditLayout->addWidget(_lineEditUsernameLabel);
    usernameLineEditLayout->addWidget(_lineEditUsername);

    QHBoxLayout *passwordLineEditLayout = new QHBoxLayout;
    passwordLineEditLayout->addWidget(_lineEditPasswordLabel);
    passwordLineEditLayout->addWidget(_lineEditPassword);

    _mainLayout->addLayout(usernameLineEditLayout);
    _mainLayout->addLayout(passwordLineEditLayout);
    _mainLayout->addWidget(_buttonBox);

    this->setLayout(_mainLayout);

    connect(_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(_buttonBox, SIGNAL(QDialogButtonBox::accepted), this, SLOT(loginActionCalled()));
}

void loginDialog::loginActionCalled(){
    qDebug() << "loginActionCalled() called";

    emit sendLoginCredentials(this->_lineEditUsername->text(), this->_lineEditPassword->text());
}






























