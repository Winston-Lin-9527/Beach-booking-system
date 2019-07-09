#ifndef BOOKINGWINDOW_H
#define BOOKINGWINDOW_H

#include <QWidget>
#include <QTabWidget>

class BookingWindow : public QWidget
{
    Q_OBJECT

public:
    BookingWindow();

private:
    QTabWidget *_itemTabWidget;

    QWidget *_firstPage;
    QWidget *_secondPage;
};

#endif // BOOKINGWINDOW_H
