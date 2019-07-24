#ifndef ITEMBOOKINGFORM_H
#define ITEMBOOKINGFORM_H

#include <QDialog>
#include <QGridLayout>

class ItemBookingForm : public QDialog
{
    Q_OBJECT

public:
    ItemBookingForm();

private:
    QGridLayout *_mLayout;


};

#endif // ITEMBOOKINGFORM_H
