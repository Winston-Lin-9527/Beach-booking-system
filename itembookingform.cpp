#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QDateTimeEdit>

#include "itembookingform.h"

ItemBookingForm::ItemBookingForm(){
    this->_productID = _counter;
    _counter++;

    this->_mLayout = new QHBoxLayout;
    this->_rightLayout = new QVBoxLayout;

    this->_durationSelectionGroupBox = new QGroupBox("How Long Would You Hire For?");
    this->_durationButtonLayout = new QVBoxLayout;
    this->_30minsCheckBox = new QCheckBox("30 Minutes");
    this->_60minsCheckBox = new QCheckBox("60 Minutes");
    _durationButtonLayout->addWidget(_30minsCheckBox);
    _durationButtonLayout->addWidget(_60minsCheckBox);
    _durationSelectionGroupBox->setLayout(_durationButtonLayout);
    _30minsCheckBox->setCheckState(Qt::CheckState::Checked);    // by default 30 mins package is selected

    this->_timeSelectionGroupBox = new QGroupBox("Choose Your Time");
    this->_dateTimeEditLayout = new QHBoxLayout;
    this->_dateTimeEdit = new QDateTimeEdit(QDate::currentDate());
    _dateTimeEdit->setMinimumDate(QDate::currentDate().addDays(-365));
    _dateTimeEdit->setMaximumDate(QDate::currentDate().addDays(365));
    _dateTimeEdit->setDisplayFormat("yyyy.MM.dd.h:m:s ap");
    _dateTimeEditLayout->addWidget(_dateTimeEdit);
    _timeSelectionGroupBox->setLayout(_dateTimeEditLayout);

    this->_quantitySelectionGroupBox = new QGroupBox("Choose How Many You Need");
    this->_quantityEditLayout = new QHBoxLayout;
    this->_quantityComboBox = new QComboBox;
    _quantityComboBox->addItems(QStringList() << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8");
    _quantityEditLayout->addWidget(_quantityComboBox);
    _quantitySelectionGroupBox->setLayout(_quantityEditLayout);

    this->_confirmButton = new QPushButton("Continue");

    QString productBannerPath;
    switch(_productID){
    case 1:
        productBannerPath = ":/resources/images/surfing.png";
        break;
    case 2:
        productBannerPath = ":/resources/images/kitesurfing.png";
        break;
    case 3:
        productBannerPath = ":/resources/images/dinghie.png";
        break;
    case 4:
        productBannerPath = ":/resources/images/keelboat.png";
        break;
    case 5:
        productBannerPath = ":/resources/images/multihulls.jpg";
        break;
    case 6:
        productBannerPath = ":/resources/images/sailing.png";
        break;
    case 7:
        productBannerPath = ":/resources/images/paddleboarding.jpg";
        break;
    case 8:
        productBannerPath = ":/resources/images/seakayaking.jpg";
        break;
    case 9:
        productBannerPath = ":/resources/images/snorkel.jpg";
        break;
    case 10:
        productBannerPath = ":/resources/images/scuba.jpg";
        break;
    case 11:
        productBannerPath = ":/resources/images/deepdiving.jpg";
        break;
    }

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
}
