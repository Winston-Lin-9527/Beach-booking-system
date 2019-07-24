#include <QApplication>
#include <QSplashScreen>

#include "mainwindow.h"
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/resources/images/surfing.png");
    QSplashScreen splash(pixmap);
    splash.show();

    if(!createConnection())
        return 1;

    MainWindow mainWindow;

    mainWindow.show();

    splash.finish(&mainWindow);

    destroyConnection();

    return a.exec();
}
