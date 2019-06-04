#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QVBoxLayout>

class QDialogButtonBox;;
class QPushButton;

class loginDialog : public QDialog
{

    Q_OBJECT

public:
    loginDialog();

signals:
    void loginButtonClicked();


private:
    QDialogButtonBox *_buttonBox;

    QVBoxLayout *_mainLayout;
};

#endif // LOGINDIALOG_H
