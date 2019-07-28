#ifndef ITEMBOOKINGFORM_H
#define ITEMBOOKINGFORM_H

#include <QDialog>

class QPushButton;
class QButtonGroup;
class QLabel;
class QHBoxLayout;
class QVBoxLayout;
class QGroupBox;
class QCheckBox;
class QDateEdit;
class QTimeEdit;
class QComboBox;
class databasehandler;

class ItemBookingForm : public QDialog
{
    Q_OBJECT

public:
    ItemBookingForm();
    void setCustomerID(QString ID);

    static int _counter;

private slots:
    void handleConfirmButtonClick();
    // todo: handle two checkBoxes, need to be opposite

private:
    QHBoxLayout *_mLayout;
    QVBoxLayout *_rightLayout;

    QVBoxLayout *_durationButtonLayout;
    QButtonGroup *_hourButtonGroup;
    QCheckBox *_30minsCheckBox;
    QCheckBox *_60minsCheckBox;

    QHBoxLayout *_dateTimeEditLayout;
    QDateEdit *_dateEdit;
    QTimeEdit *_timeEdit;

    QHBoxLayout *_quantityEditLayout;
    QComboBox *_quantityComboBox;

    QPushButton *_confirmButton;

    QGroupBox *_durationSelectionGroupBox;
    QGroupBox *_timeSelectionGroupBox;
    QGroupBox *_quantitySelectionGroupBox;

    QLabel *_productBanner;

    int _productID;
    QString _customerID;
};

#endif // ITEMBOOKINGFORM_H
