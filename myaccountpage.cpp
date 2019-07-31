#include <QTableWidget>
#include <QList>
#include <QGridLayout>
#include <QStringList>
#include <QDebug>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>

#include "myaccountpage.h"
#include "databasehandler.h"

QString giveProductName(int productID){
    switch(productID){
    case 1:
        return QString("Surfing");
    case 2:
        return QString("Kite Surfing");
    case 3:
        return QString("Hobie");
    case 4:
        return QString("Keelboats & yachts");
    case 5:
        return QString("Multi-hulls");
    case 6:
        return QString("Laser Sailing");
    case 7:
        return QString("Paddle boarding");
    case 8:
        return QString("Sea Kayaking");
    case 9:
        return QString("Snorkeling");
    case 10:
        return QString("Scuba diving");
    case 11:
        return QString("Deep sea diving");
    case 12:
        return QString("Parasailing");
    case 13:
        return QString("Skydiving");
    }
    return QString();
}

MyAccountPage::MyAccountPage()
{

    this->_bookingRecordTable = new QTableWidget(this);
    _bookingRecordTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _bookingRecordTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    _bookingRecordTable->setColumnCount(5);
    QStringList horizontalLabels = { "Product Type", "Quantity", "Date", "Time", "Duration"};
    _bookingRecordTable->setHorizontalHeaderLabels(horizontalLabels);

    this->_activeBookingLabel = new QLabel("Your Active Bookings");
    QFont font;
    font.setBold(true);
    font.setPointSize(25);
    _activeBookingLabel->setFont(font);

    this->_balanceLabel = new QLabel;
    this->_topupButton = new QPushButton("Confirm");
    this->_topupLabel = new QLabel("Top up: ");
    this->_topupSpinBox = new QSpinBox;
    _topupSpinBox->setRange(0, 999);
    _topupSpinBox->setPrefix("$ ");

    QHBoxLayout *balanceHLayout = new QHBoxLayout;
    balanceHLayout->addWidget(_balanceLabel);
    balanceHLayout->addWidget(_topupLabel);
    balanceHLayout->addWidget(_topupSpinBox);
    balanceHLayout->addWidget(_topupButton);

    balanceHLayout->setStretch(0, 5);
    balanceHLayout->setStretch(1, 1);
    balanceHLayout->setStretch(2, 3);
    balanceHLayout->setStretch(3, 1);

    this->_mLayout = new QGridLayout;
    _mLayout->addWidget(_activeBookingLabel, 0, 0);
    _mLayout->addLayout(balanceHLayout, 1, 0);
    _mLayout->addWidget(_balanceLabel, 2, 0);
    _mLayout->addWidget(_bookingRecordTable, 3, 0);

    this->setLayout(_mLayout);
    this->setFixedSize(QSize(560, 400));

    connect(_topupButton, SIGNAL(clicked()), this, SLOT(topupButtonClicked()));
}

void MyAccountPage::openPage(QString accountID, int balance){
    QString balanceText("Your balance: $");
    balanceText += QString::number(balance);
    _balance = balance;

    _balanceLabel->setText(balanceText);

    databasehandler handler;
    handler.loadFromFile();
    QList<Booking> loadedList = handler.getBookings();
    QList<Booking> filteredList;

    for(int i = 0; i < loadedList.size(); i++)
        if(loadedList.at(i).customerID == accountID){
            filteredList.append(loadedList.at(i));
        }

    _bookingRecordTable->clearContents();
    _bookingRecordTable->setRowCount(filteredList.size());

    for(int i = 0; i < filteredList.size(); i++){
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setData(Qt::DisplayRole, giveProductName(filteredList.at(i).productID));
        item->setTextAlignment(Qt::AlignCenter);
        this->_bookingRecordTable->setItem(i, 0, item);

        QTableWidgetItem *quantityItem = new QTableWidgetItem;
        quantityItem->setData(Qt::DisplayRole, filteredList.at(i).quantity);
        quantityItem->setTextAlignment(Qt::AlignCenter);
        this->_bookingRecordTable->setItem(i, 1, quantityItem);

        this->_bookingRecordTable->setItem(i, 2, new QTableWidgetItem(filteredList.at(i).date.toString("yyyy.MM.dd")));
        this->_bookingRecordTable->setItem(i, 3, new QTableWidgetItem(filteredList.at(i).startTime.toString("H:m")));

        QTableWidgetItem *durationItem = new QTableWidgetItem;
        durationItem->setData(Qt::DisplayRole, filteredList.at(i).duration30mins == true ? "30 Mins" : "60 Mins");
        durationItem->setTextAlignment(Qt::AlignCenter);
        this->_bookingRecordTable->setItem(i, 4, durationItem);
    }
    this->open();
}

void MyAccountPage::topupButtonClicked(){
    this->_balanceLabel->setText("Your balance: $" + QString::number(this->_topupSpinBox->value() + _balance));
    _balance = this->_topupSpinBox->value() + _balance;
    emit balanceChanged(this->_topupSpinBox->value() + _balance);
}
