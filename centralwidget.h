#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QWidget>

class QLabel;
class QStackedWidget;
class QPushButton;

class CentralWidget : public QWidget
{
    Q_OBJECT

public:
    CentralWidget(QWidget *parent = 0);
    virtual ~CentralWidget();

public slots:
    void lmao();

private:
    QStackedWidget *_stackedWindows;
    QPushButton *_bookingButton;
    QPushButton *_createAccountButton;
    QLabel *_label;
    QLabel *_label2;
};

#endif // CENTRALWIDGET_H
