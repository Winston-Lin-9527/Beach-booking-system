#include <QtDebug>

#include "bookingwindow.h"
#include "packagedisplaycell.h"

int ItemBookingForm::_counter = 1;

BookingWindow::BookingWindow()
{
    this->_itemTabWidget = new QTabWidget;

    this->_firstPage = new QWidget;
    this->_secondPage = new QWidget;
    this->_thirdPage = new QWidget;
    this->_fourthPage = new QWidget;
    this->_fifthPage = new QWidget;

    this->_categoryOneScrollArea = new QScrollArea;
    this->_categoryTwoScrollArea = new QScrollArea;
    this->_categoryThreeScrollArea = new QScrollArea;
    this->_categoryFourScrollArea = new QScrollArea;
    this->_categoryFiveScrollArea = new QScrollArea;

    this->_itemDisplayGridLayout_CategoryOne = new QGridLayout;
    this->_itemDisplayGridLayout_CategoryTwo = new QGridLayout;
    this->_itemDisplayGridLayout_CategoryThree = new QGridLayout;
    this->_itemDisplayGridLayout_CategoryFour = new QGridLayout;
    this->_itemDisplayGridLayout_CategoryFive = new QGridLayout;

    this->_backButton = new QPushButton("Back");
    _backButton->setMaximumWidth(100);

    // initialize the package cells
    // first category
    PackageDisplayCell *cell1 = new PackageDisplayCell(1, "Surfing", ":/resources/images/surf.jpg");
    PackageDisplayCell *cell2 = new PackageDisplayCell(2, "Kite Surfing", ":/resources/images/kitesurfing.png");

    // second category..
    PackageDisplayCell *cell3 = new PackageDisplayCell(3, "Hobie", ":/resources/images/hobie.jpg");
    PackageDisplayCell *cell4 = new PackageDisplayCell(4, "Keelboats & yachts", ":/resources/images/keelboat.png");
    PackageDisplayCell *cell5 = new PackageDisplayCell(5, "Multi-hulls", ":/resources/images/multihulls.jpg");
    PackageDisplayCell *cell6 = new PackageDisplayCell(6, "Laser Sailing", ":/resources/images/sailing.jpg");

    // third category
    PackageDisplayCell *cell7 = new PackageDisplayCell(7, "Paddle boarding", ":/resources/images/paddleboarding.jpg");
    PackageDisplayCell *cell8 = new PackageDisplayCell(8, "Sea Kayaking", ":/resources/images/seakayaking.jpg");

    // fourth category
    PackageDisplayCell *cell9 = new PackageDisplayCell(9, "Snorkeling", ":/resources/images/snorkel.jpg");
    PackageDisplayCell *cell10 = new PackageDisplayCell(10, "Scuba diving", ":/resources/images/scuba.jpg");
    PackageDisplayCell *cell11 = new PackageDisplayCell(11, "Deep sea diving", ":/resources/images/deepdiving.jpg");

    // fifth category
    PackageDisplayCell *cell12 = new PackageDisplayCell(12, "Parasailing", ":/resources/images/parasailing.jpg");
    PackageDisplayCell *cell13 = new PackageDisplayCell(13, "Skydiving", ":/resources/images/skydive.jpg");

    // add extra staffs to the pages
    this->_labelCategoryOne = new QLabel("Lets buy some sailing gears");
    this->_labelCategoryTwo = new QLabel("Lets buy some swimming gears");

//    _itemDisplayGridLayout_CategoryOne->addWidget(_labelCategoryTwo, 0, 1);
//    _itemDisplayGridLayout_CategoryOne->addWidget(_labelCategoryOne, 2, 0);
    _itemDisplayGridLayout_CategoryOne->addWidget(cell1, 0, 0);
    _itemDisplayGridLayout_CategoryOne->addWidget(cell2, 0, 1);

    _itemDisplayGridLayout_CategoryTwo->addWidget(cell3, 0, 0);
    _itemDisplayGridLayout_CategoryTwo->addWidget(cell4, 0, 1);
    _itemDisplayGridLayout_CategoryTwo->addWidget(cell5, 1, 0);
    _itemDisplayGridLayout_CategoryTwo->addWidget(cell6, 1, 1);

    _itemDisplayGridLayout_CategoryThree->addWidget(cell7, 0, 0);
    _itemDisplayGridLayout_CategoryThree->addWidget(cell8, 0, 1);

    _itemDisplayGridLayout_CategoryFour->addWidget(cell9, 0, 0);
    _itemDisplayGridLayout_CategoryFour->addWidget(cell10, 0, 1);
    _itemDisplayGridLayout_CategoryFour->addWidget(cell11, 1, 0);

    _itemDisplayGridLayout_CategoryFive->addWidget(cell12, 0, 0);
    _itemDisplayGridLayout_CategoryFive->addWidget(cell13, 0, 1);

    _firstPage->setLayout(_itemDisplayGridLayout_CategoryOne);
    _secondPage->setLayout(_itemDisplayGridLayout_CategoryTwo);
    _thirdPage->setLayout(_itemDisplayGridLayout_CategoryThree);
    _fourthPage->setLayout(_itemDisplayGridLayout_CategoryFour);
    _fifthPage->setLayout(_itemDisplayGridLayout_CategoryFive);

    _categoryOneScrollArea->setWidget(_firstPage);
    _categoryTwoScrollArea->setWidget(_secondPage);
    _categoryThreeScrollArea->setWidget(_thirdPage);
    _categoryFourScrollArea->setWidget(_fourthPage);
    _categoryFiveScrollArea->setWidget(_fifthPage);

    _itemTabWidget->addTab(_categoryOneScrollArea, "Surfing");
    _itemTabWidget->addTab(_categoryTwoScrollArea, "Sailing");
    _itemTabWidget->addTab(_categoryThreeScrollArea, "Paddling");
    _itemTabWidget->addTab(_categoryFourScrollArea, "Diving");
    _itemTabWidget->addTab(_categoryFiveScrollArea, "Special");

    this->_mLayout = new QVBoxLayout;
    _mLayout->addWidget(_backButton);
    _mLayout->addWidget(_itemTabWidget);

    setLayout(_mLayout);

    // connect clicks to display bookingForms
    connect(cell1, SIGNAL(clickedSignal()), this, SLOT(showBookingForm()));
    connect(cell2, SIGNAL(clickedSignal()), this, SLOT(showBookingForm()));
    connect(cell3, SIGNAL(clickedSignal()), this, SLOT(showBookingForm()));
    connect(cell4, SIGNAL(clickedSignal()), this, SLOT(showBookingForm()));
    connect(cell5, SIGNAL(clickedSignal()), this, SLOT(showBookingForm()));
    connect(cell6, SIGNAL(clickedSignal()), this, SLOT(showBookingForm()));
    connect(cell7, SIGNAL(clickedSignal()), this, SLOT(showBookingForm()));
    connect(cell8, SIGNAL(clickedSignal()), this, SLOT(showBookingForm()));
    connect(cell9, SIGNAL(clickedSignal()), this, SLOT(showBookingForm()));
    connect(cell10, SIGNAL(clickedSignal()), this, SLOT(showBookingForm()));
    connect(cell11, SIGNAL(clickedSignal()), this, SLOT(showBookingForm()));
    connect(cell12, SIGNAL(clickedSignal()), this, SLOT(showBookingForm()));
    connect(cell13, SIGNAL(clickedSignal()), this, SLOT(showBookingForm()));

    connect(&form1, SIGNAL(balanceChanged(int)), this, SIGNAL(balanceChanged(int)));
    connect(&form2, SIGNAL(balanceChanged(int)), this, SIGNAL(balanceChanged(int)));
    connect(&form3, SIGNAL(balanceChanged(int)), this, SIGNAL(balanceChanged(int)));
    connect(&form4, SIGNAL(balanceChanged(int)), this, SIGNAL(balanceChanged(int)));
    connect(&form5, SIGNAL(balanceChanged(int)), this, SIGNAL(balanceChanged(int)));
    connect(&form6, SIGNAL(balanceChanged(int)), this, SIGNAL(balanceChanged(int)));
    connect(&form7, SIGNAL(balanceChanged(int)), this, SIGNAL(balanceChanged(int)));
    connect(&form8, SIGNAL(balanceChanged(int)), this, SIGNAL(balanceChanged(int)));
    connect(&form9, SIGNAL(balanceChanged(int)), this, SIGNAL(balanceChanged(int)));
    connect(&form10, SIGNAL(balanceChanged(int)), this, SIGNAL(balanceChanged(int)));
    connect(&form11, SIGNAL(balanceChanged(int)), this, SIGNAL(balanceChanged(int)));
    connect(&form12, SIGNAL(balanceChanged(int)), this, SIGNAL(balanceChanged(int)));
    connect(&form13, SIGNAL(balanceChanged(int)), this, SIGNAL(balanceChanged(int)));

    connect(_backButton, SIGNAL(clicked()), this, SLOT(backButtonClicked()));
}

void BookingWindow::backButtonClicked(){
    emit signalBackToHomePage();
}

void BookingWindow::showBookingForm(){
    qDebug() << "BookingWindow::showBookingForm() called";

    /* find out the sender of the signal using sender(), this function returns the sender as QObject*
    /  since we know the sender is an ItemBookingForm object, it is safe to cast the QObject* into its derived class
    /  being defensive using qobject_cast, if casting fails, a null pointer is returned
    */
    PackageDisplayCell *triggeredCell = qobject_cast<PackageDisplayCell *>(sender());

    int ID = triggeredCell->ID();
    switch(ID){
    case 1:
        form1.exec();
        break;
    case 2:
        form2.exec();
        break;
    case 3:
        form3.exec();
        break;
    case 4:
        form4.exec();
        break;
    case 5:
        form5.exec();
        break;
    case 6:
        form6.exec();
        break;
    case 7:
        form7.exec();
        break;
    case 8:
        form8.exec();
        break;
    case 9:
        form9.exec();
        break;
    case 10:
        form10.exec();
        break;
    case 11:
        form11.exec();
        break;
    case 12:
        form12.exec();
        break;
    case 13:
        form13.exec();
        break;
    default:
        qDebug() << "what's happening?";
    }
}

void BookingWindow::setCustomerID(QString ID){

    form1.setCustomerID(ID);
    form2.setCustomerID(ID);
    form3.setCustomerID(ID);
    form4.setCustomerID(ID);
    form5.setCustomerID(ID);
    form6.setCustomerID(ID);
    form7.setCustomerID(ID);
    form8.setCustomerID(ID);
    form9.setCustomerID(ID);
    form10.setCustomerID(ID);
    form11.setCustomerID(ID);
    form12.setCustomerID(ID);
    form13.setCustomerID(ID);
}

void BookingWindow::setBalance(int balance){
    form1.setBalance(balance);
    form2.setBalance(balance);
    form3.setBalance(balance);
    form4.setBalance(balance);
    form5.setBalance(balance);
    form6.setBalance(balance);
    form7.setBalance(balance);
    form8.setBalance(balance);
    form9.setBalance(balance);
    form10.setBalance(balance);
    form11.setBalance(balance);
    form12.setBalance(balance);
    form13.setBalance(balance);
}
