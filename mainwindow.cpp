#include "mainwindow.h"

MainWindow::MainWindow()
{
    this->_centralWidget = new CentralWidget;
    setCentralWidget(_centralWidget);
    setWindowTitle("Bitch sport Booking");
}
