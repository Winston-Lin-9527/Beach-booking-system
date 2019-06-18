#include "logindialog.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QObject>
#include <QLineEdit>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>

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
    connect(_buttonBox, &QDialogButtonBox::accepted, this, &loginDialog::loginActionCalled);
}

void loginDialog::loginActionCalled(){
    qDebug() << "loginActionCalled() called";

    if(this->_lineEditUsername->text().length() >= GLOBALS_USERNAME_MIN_CHARACTER && this->_lineEditPassword->text().length() >= GLOBALS_PASSWORD_MIN_CHARACTER)
        emit requestLogin(this->_lineEditUsername->text(), this->_lineEditPassword->text());

    else{
        QMessageBox::warning(this, "Error", "Please login using credentials in valid form"); }
}

void loginDialog::handleReturnStatus(StatusCode statusCode){
    QMessageBox *msgBox = new QMessageBox;

    if(statusCode == StatusCode::LOGIN_SUCCESS){
        msgBox->setText("Login successful.");
        msgBox->setInformativeText("");
        msgBox->setStandardButtons(QMessageBox::Ok);
        msgBox->setDefaultButton(QMessageBox::Ok);
        msgBox->exec();
        this->close();
    }

    else if (statusCode == StatusCode::LOGIN_FAILURE_NONMATCHING_CREDENTIALS){
        msgBox->setText("Login Failure");
        msgBox->setInformativeText("The credentials don't match to our record.");
        msgBox->setStandardButtons(QMessageBox::Retry | QMessageBox::Cancel);
        msgBox->setDefaultButton(QMessageBox::Retry);
        int result = msgBox->exec();

        if(result == QMessageBox::Cancel)
            this->close();          // close the loginDialog if the user wants to give up, else if retry button clicked stay at the dialog
    }
}




























