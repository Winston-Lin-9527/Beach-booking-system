#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
 *  really just a wrapper for the main widget
 */

#include <QMainWindow>
#include "centralwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();

private:
    CentralWidget *_centralWidget;
};

#endif // MAINWINDOW_H
