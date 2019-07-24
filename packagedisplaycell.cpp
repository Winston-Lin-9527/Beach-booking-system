#include <QVBoxLayout>

#include "packagedisplaycell.h"


PackageDisplayCell::PackageDisplayCell(){ }

PackageDisplayCell::PackageDisplayCell(int ID, QString packageName, QString packageBannerPath){
    this->_packageID = ID;
    this->_packageName = new QLabel(packageName);
    this->_packageBanner = new QLabel;
    _packageBanner->resize(200, 200);   // standard dimensions of a banner
    this->_bookButton = new QPushButton("Book");

    QImage bannerImage(packageBannerPath);
    QPixmap bannerPixmap = QPixmap::fromImage(bannerImage);
    QPixmap processedPixmap = bannerPixmap.scaled(_packageBanner->size(), Qt::KeepAspectRatio);
    _packageBanner->setPixmap(processedPixmap);

    _packageBanner->setFrameStyle( QFrame::Panel | QFrame::Raised );
    _packageName->setFrameStyle( QFrame::Panel | QFrame::Raised );

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(_packageBanner);
    layout->addWidget(_packageName);
    layout->addWidget(_bookButton);

    this->setFrameStyle( QFrame::Panel | QFrame::Raised );
    this->setLayout(layout);

    connect(_bookButton, SIGNAL(clicked()), this, SLOT(bookButtonClicked()));
}

void PackageDisplayCell::bookButtonClicked(){
    emit clickedSignal();
}

int PackageDisplayCell::ID() const{
    return _packageID;
}
