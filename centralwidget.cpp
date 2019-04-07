#include "centralwidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QPushButton>

CentralWidget::CentralWidget(QWidget *parent)
{
    this->_stackedWindows = new QStackedWidget;

    _label = new QLabel("this is the bitch sport");
    _label2 = new QLabel("create account?");

    _createAccountButton = new QPushButton("create account");

    _stackedWindows->addWidget(_label);
    _stackedWindows->addWidget(_label2);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(5);
    mainLayout->addWidget(_stackedWindows);
    mainLayout->addWidget(_createAccountButton);

    connect(_createAccountButton, SIGNAL(clicked()), this, SLOT(lmao()));
}

CentralWidget::~CentralWidget(){}

void CentralWidget::lmao(){
    _stackedWindows->setCurrentIndex(_stackedWindows->currentIndex()+1);
}



