#ifndef BOOKINGWINDOW_H
#define BOOKINGWINDOW_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QLabel>

class BookingWindow : public QWidget
{
    Q_OBJECT

public:
    BookingWindow();

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

    QGridLayout *_itemDisplayGridLayout_CategoryOne;
    QGridLayout *_itemDisplayGridLayout_CategoryTwo;
};

#endif // BOOKINGWINDOW_H
