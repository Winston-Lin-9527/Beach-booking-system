#include "logindialog.h"

#include <QDialogButtonBox>
#include <QPushButton>
#include <QObject>

loginDialog::loginDialog() : QDialog()
{
    _buttonBox = new QDialogButtonBox();
    _buttonBox->addButton(QString("Login"), QDialogButtonBox::AcceptRole);
    _buttonBox->addButton("Cancel", QDialogButtonBox::RejectRole);

    _mainLayout = new QVBoxLayout;

    _mainLayout->addWidget(_buttonBox);

    this->setLayout(_mainLayout);

    connect(_buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

