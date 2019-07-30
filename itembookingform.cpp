#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QTimeEdit>
#include <QDateEdit>
#include <QtDebug>
#include <QButtonGroup>
#include <QMessageBox>

#include "itembookingform.h"
#include "databasehandler.h"

ItemBookingForm::ItemBookingForm(){
    this->_productID = _counter;
    _counter++;

    QString productBannerPath;
    QTime lowerBound;
    QTime upperBound;

    // hardcode the time boundary for each product kind(tide), which kind of makes sense although ugly
    switch(_productID){
    case 1:
        productBannerPath = ":/resources/images/surf.jpg";
        _price = 50;
        lowerBound = QTime(2, 23);
        upperBound = QTime(5, 23);
        break;
    case 2:
        productBannerPath = ":/resources/images/kitesurfing.png";
        _price = 70;
        lowerBound = QTime();
        upperBound = QTime();
        break;
    case 3:
        productBannerPath = ":/resources/images/hobie.jpg";
        _price = 100;
        lowerBound = QTime();
        upperBound = QTime();
        break;
    case 4:
        productBannerPath = ":/resources/images/keelboat.png";
        _price = 100;
        lowerBound = QTime();
        upperBound = QTime();
        break;
    case 5:
        productBannerPath = ":/resources/images/multihulls.jpg";
        _price = 100;
        lowerBound = QTime();
        upperBound = QTime();
        break;
    case 6:
        productBannerPath = ":/resources/images/sailing.png";
        _price = 150;
        lowerBound = QTime();
        upperBound = QTime();
        break;
    case 7:
        productBannerPath = ":/resources/images/paddleboarding.jpg";
        _price = 100;
        lowerBound = QTime();
        upperBound = QTime();
        break;
    case 8:
        productBannerPath = ":/resources/images/seakayaking.jpg";
        _price = 120;
        lowerBound = QTime();
        upperBound = QTime();
        break;
    case 9:
        productBannerPath = ":/resources/images/snorkel.jpg";
        _price = 150;
        lowerBound = QTime();
        upperBound = QTime();
        break;
    case 10:
        productBannerPath = ":/resources/images/scuba.jpg";
        _price = 100;
        lowerBound = QTime();
        upperBound = QTime();
        break;
    case 11:
        productBannerPath = ":/resources/images/deepdiving.jpg";
        _price = 100;
        lowerBound = QTime();
        upperBound = QTime();
        break;
    case 12:
        productBannerPath = ":/resources/images/parasailing.jpg";
        _price = 300;
        lowerBound = QTime();
        upperBound = QTime();
        break;
    case 13:
        productBannerPath = ":/resources/images/skydive.jpg";
        _price = 500;
        lowerBound = QTime();
        upperBound = QTime();
        break;
    }

    QFont font;
    font.setBold(true);
    font.setPointSize(20);
    font.setWeight(60);

    this->_mLayout = new QHBoxLayout;
    this->_rightLayout = new QVBoxLayout;

    this->_durationSelectionGroupBox = new QGroupBox("How Long Would You Hire For?");
    _durationSelectionGroupBox->setFont(font);
    this->_durationButtonLayout = new QVBoxLayout;
    this->_30minsCheckBox = new QCheckBox("30 Minutes");
    this->_60minsCheckBox = new QCheckBox("60 Minutes");
    this->_hourButtonGroup = new QButtonGroup;
    _hourButtonGroup->addButton(_30minsCheckBox);
    _hourButtonGroup->addButton(_60minsCheckBox);
    _durationButtonLayout->addWidget(_30minsCheckBox);
    _durationButtonLayout->addWidget(_60minsCheckBox);
    _durationSelectionGroupBox->setLayout(_durationButtonLayout);
    _30minsCheckBox->setCheckState(Qt::CheckState::Checked);    // by default 30 mins package is selected

    this->_timeSelectionGroupBox = new QGroupBox("Choose Your Time");
    _timeSelectionGroupBox->setFont(font);
    this->_dateTimeEditLayout = new QHBoxLayout;
    this->_dateEdit = new QDateEdit(QDate::currentDate());
    this->_timeEdit = new QTimeEdit(QTime::currentTime());
    _dateEdit->setMinimumDate(QDate::currentDate().addDays(-365));
    _dateEdit->setMaximumDate(QDate::currentDate().addDays(365));
    _dateEdit->setDisplayFormat("yyyy.MM.dd");
    _timeEdit->setTimeRange(lowerBound, upperBound);
    _timeEdit->setDisplayFormat("H:m:s");
    _dateTimeEditLayout->addWidget(_dateEdit);
    _dateTimeEditLayout->addWidget(_timeEdit);
    _timeSelectionGroupBox->setLayout(_dateTimeEditLayout);

    this->_quantitySelectionGroupBox = new QGroupBox("Choose How Many You Need");
    _quantitySelectionGroupBox->setFont(font);
    this->_quantityEditLayout = new QHBoxLayout;
    this->_quantityComboBox = new QComboBox;
    _quantityComboBox->addItems(QStringList() << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8");
    _quantityEditLayout->addWidget(_quantityComboBox);
    _quantitySelectionGroupBox->setLayout(_quantityEditLayout);

    this->_confirmButton = new QPushButton("Pay Now ($" + QString::number(_price) + ")");

    this->_productBanner = new QLabel;
    QImage bannerImage(productBannerPath);
    QPixmap bannerPixmap = QPixmap::fromImage(bannerImage);
    QPixmap processedPixmap = bannerPixmap.scaled(_productBanner->size(), Qt::KeepAspectRatio);
    _productBanner->setPixmap(processedPixmap);

    _rightLayout->addWidget(_durationSelectionGroupBox);
    _rightLayout->addWidget(_timeSelectionGroupBox);
    _rightLayout->addWidget(_quantitySelectionGroupBox);
    _rightLayout->addWidget(_confirmButton);

    _mLayout->addWidget(_productBanner);
    _mLayout->addLayout(_rightLayout);

    this->setLayout(_mLayout);

    connect(_confirmButton, SIGNAL(clicked()), this, SLOT(handleConfirmButtonClick()));
}

void ItemBookingForm::handleConfirmButtonClick(){
   databasehandler handler;
   handler.loadFromFile();

   Booking newBooking = {
       QString(handler.getBookings().size()),
       this->_customerID,
       this->_productID,
       this->_dateEdit->date(),
       this->_timeEdit->time(),
       this->_30minsCheckBox->isChecked(),
       this->_quantityComboBox->currentText().toInt()
   };

   if((this->_30minsCheckBox->isChecked() ? _price : _price * 2)*this->_quantityComboBox->currentText().toInt() < _balance){
       if(!handler.checkTimeCollision(newBooking)){
           qDebug()<<"This item is added under the name of " << this->_customerID;

           handler.addBooking(newBooking);
           handler.saveToFile();

           emit balanceChanged(_balance - (this->_30minsCheckBox->isChecked() ? _price : _price * 2)*this->_quantityComboBox->currentText().toInt());

           QMessageBox::about(this, "success", "New Booking has been added");
       }
       else
           QMessageBox::warning(this, "Error", "This new booking is in time conflict with one of your existing booking.");
   }
   else
       QMessageBox::warning(this, "Transaction Failure", "Insufficient balance, please top up");
}

void ItemBookingForm::setCustomerID(QString ID){
    this->_customerID = ID;
}

void ItemBookingForm::setBalance(int balance){
    this->_balance = balance;
}
