#ifndef BOOKINGWINDOW_H
#define BOOKINGWINDOW_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>

#include <itembookingform.h>


class BookingWindow : public QWidget
{
    Q_OBJECT

public:
    BookingWindow();
    void setCustomerID(QString ID);

signals:
    void signalBackToHomePage();

private slots:
    void backButtonClicked();
    void showBookingForm();

private:
    // the widgets listed are in top down order

    QVBoxLayout *_mLayout;

    QTabWidget *_itemTabWidget;

    QLabel *_labelCategoryOne;
    QLabel *_labelCategoryTwo;

    QScrollArea *_categoryOneScrollArea;
    QScrollArea *_categoryTwoScrollArea;
    QScrollArea *_categoryThreeScrollArea;
    QScrollArea *_categoryFourScrollArea;
    QScrollArea *_categoryFiveScrollArea;

    QWidget *_firstPage;
    QWidget *_secondPage;
    QWidget *_thirdPage;
    QWidget *_fourthPage;
    QWidget *_fifthPage;

    QPushButton *_backButton;

    QGridLayout *_itemDisplayGridLayout_CategoryOne;
    QGridLayout *_itemDisplayGridLayout_CategoryTwo;
    QGridLayout *_itemDisplayGridLayout_CategoryThree;
    QGridLayout *_itemDisplayGridLayout_CategoryFour;
    QGridLayout *_itemDisplayGridLayout_CategoryFive;

    // this is so f-cking ugly, ewwww
    // but if use elegant way there are issues with copy contructor and overload resolution
    ItemBookingForm form1;
    ItemBookingForm form2;
    ItemBookingForm form3;
    ItemBookingForm form4;
    ItemBookingForm form5;
    ItemBookingForm form6;
    ItemBookingForm form7;
    ItemBookingForm form8;
    ItemBookingForm form9;
    ItemBookingForm form10;
    ItemBookingForm form11;
    ItemBookingForm form12;
    ItemBookingForm form13;

    QString _customerID;
};

#endif // BOOKINGWINDOW_H
