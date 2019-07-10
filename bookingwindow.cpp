#include "bookingwindow.h"

BookingWindow::BookingWindow()
{
    this->_itemTabWidget = new QTabWidget;

    this->_firstPage = new QWidget;
    this->_secondPage = new QWidget;

    this->_categoryOneScrollArea = new QScrollArea;
    this->_categoryTwoScrollArea = new QScrollArea;

    this->_itemDisplayGridLayout_CategoryOne = new QGridLayout;
    this->_itemDisplayGridLayout_CategoryTwo = new QGridLayout;

    // add staffs to the two pages now
    this->_labelCategoryOne = new QLabel("Lets buy some sailing gears");
    this->_labelCategoryTwo = new QLabel("Lets buy some swimming gears");

    _itemDisplayGridLayout_CategoryOne->addWidget(_labelCategoryTwo, 0, 1);
    _itemDisplayGridLayout_CategoryOne->addWidget(_labelCategoryOne, 1, 0);

    _firstPage->setLayout(_itemDisplayGridLayout_CategoryOne);
    _secondPage->setLayout(_itemDisplayGridLayout_CategoryTwo);

    _categoryOneScrollArea->setWidget(_firstPage);
    _categoryTwoScrollArea->setWidget(_secondPage);

    this->_subFirstPageVLayout = new QVBoxLayout;
    this->_subSecondPageVLayout = new QVBoxLayout;

    _subFirstPageVLayout->addWidget(_categoryOneScrollArea);
    _subSecondPageVLayout->addWidget(_categoryTwoScrollArea);

    _itemTabWidget->addTab(_categoryOneScrollArea, "sail");
    _itemTabWidget->addTab(_categoryTwoScrollArea, "swim");

    this->_mLayout = new QVBoxLayout;
    _mLayout->addWidget(_itemTabWidget);

    setLayout(_mLayout);
}
