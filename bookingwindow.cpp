#include "bookingwindow.h"
#include "packagedisplaycell.h"

BookingWindow::BookingWindow()
{
    this->_itemTabWidget = new QTabWidget;

    this->_firstPage = new QWidget;
    this->_secondPage = new QWidget;

    this->_categoryOneScrollArea = new QScrollArea;
    this->_categoryTwoScrollArea = new QScrollArea;
    this->_categoryThreeScrollArea = new QScrollArea;
    this->_categoryFourScrollArea = new QScrollArea;
    this->_categoryFiveScrollArea = new QScrollArea;

    this->_itemDisplayGridLayout_CategoryOne = new QGridLayout;
    this->_itemDisplayGridLayout_CategoryTwo = new QGridLayout;

    // initialize the package cells
    // first category
    PackageDisplayCell *cell = new PackageDisplayCell(9, "package name", ":/resources/visaicon.png", SportKindOnTide::HIGH_TIDE);


    // second category

    // add staffs to the two pages now
    this->_labelCategoryOne = new QLabel("Lets buy some sailing gears");
    this->_labelCategoryTwo = new QLabel("Lets buy some swimming gears");

//    _itemDisplayGridLayout_CategoryOne->addWidget(_labelCategoryTwo, 0, 1);
//    _itemDisplayGridLayout_CategoryOne->addWidget(_labelCategoryOne, 2, 0);
    _itemDisplayGridLayout_CategoryOne->addWidget(cell, 0, 2);

    _firstPage->setLayout(_itemDisplayGridLayout_CategoryOne);
    _secondPage->setLayout(_itemDisplayGridLayout_CategoryTwo);

    _categoryOneScrollArea->setWidget(_firstPage);
    _categoryTwoScrollArea->setWidget(_secondPage);

    _itemTabWidget->addTab(_categoryOneScrollArea, "Surfing");
    _itemTabWidget->addTab(_categoryTwoScrollArea, "Sailing");
    _itemTabWidget->addTab(_categoryThreeScrollArea, "Paddling");
    _itemTabWidget->addTab(_categoryFourScrollArea, "Diving");
    _itemTabWidget->addTab(_categoryFiveScrollArea, "Special");

    this->_mLayout = new QVBoxLayout;
    _mLayout->addWidget(_itemTabWidget);

    setLayout(_mLayout);
}
