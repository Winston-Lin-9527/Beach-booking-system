#include "bookingwindow.h"
#include <QHBoxLayout>

BookingWindow::BookingWindow()
{
   this->_itemTabWidget = new QTabWidget;

   this->_firstPage = new QWidget;
   this->_secondPage = new QWidget;

   _itemTabWidget->addTab(_firstPage, "sail");
   _itemTabWidget->addTab(_secondPage, "swim");

   auto *layout = new QHBoxLayout;
   layout->addWidget(_itemTabWidget);

   setLayout(layout);

}
