#include <QApplication>

#include "mainwindow.h"
#include "connection.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!createConnection())
        return 1;

    MainWindow mainWindow;

    mainWindow.show();

    destroyConnection();

    return a.exec();
}
