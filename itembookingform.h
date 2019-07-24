#ifndef ITEMBOOKINGFORM_H
#define ITEMBOOKINGFORM_H

#include <QDialog>

class QPushButton;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class QGroupBox;
class QCheckBox;
class QDateTimeEdit;
class QComboBox;

class ItemBookingForm : public QDialog
{
    Q_OBJECT

public:
    ItemBookingForm();

    static int _counter;

private slots:
    // todo: handle two checkBoxes, need to be opposite

private:
    QHBoxLayout *_mLayout;
    QVBoxLayout *_rightLayout;

    QVBoxLayout *_durationButtonLayout;
    QCheckBox *_30minsCheckBox;
    QCheckBox *_60minsCheckBox;

    QHBoxLayout *_dateTimeEditLayout;
    QDateTimeEdit *_dateTimeEdit;

    QHBoxLayout *_quantityEditLayout;
    QComboBox *_quantityComboBox;

    QPushButton *_confirmButton;

    QGroupBox *_durationSelectionGroupBox;
    QGroupBox *_timeSelectionGroupBox;
    QGroupBox *_quantitySelectionGroupBox;

    QLabel *_productBanner;

    int _productID;
};

#endif // ITEMBOOKINGFORM_H
