#include <QApplication>
#include <QSplashScreen>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/resources/images/splashscreen.jpg");
    QSplashScreen splash(pixmap);
    splash.show();

    MainWindow mainWindow;

    mainWindow.show();

    splash.finish(&mainWindow);

    return a.exec();
}
// 4cB0
