#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QVBoxLayout>

class QDialogButtonBox;;
class QStandardButton;
class QLineEdit;
class QLabel;

/*
 *  this is a generic class used for login dialog
 */

class loginDialog : public QDialog
{

    Q_OBJECT

public:
    loginDialog();

signals:
    // no cancel button signal because can be handled by QDialog::reject in loginDialog()
    void sendLoginCredentials(QString username, QString passwordInPlainText);

private slots:
    void loginActionCalled();   // make this a slot because easier to call when a 'reject' message is seen

private:
    QDialogButtonBox *_buttonBox;
    QPushButton *_loginButton;      // need to declare this as a button to connect with clicked()
    QVBoxLayout *_mainLayout;

    QLabel *_lineEditUsernameLabel;
    QLabel *_lineEditPasswordLabel;

    QLineEdit *_lineEditUsername;
    QLineEdit *_lineEditPassword;
};

#endif // LOGINDIALOG_H
