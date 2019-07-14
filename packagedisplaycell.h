#ifndef PACKAGEDISPLAYCELL_H
#define PACKAGEDISPLAYCELL_H

#include <QLabel>
#include <QString>
#include <QPushButton>

enum SportKindOnTide{
    LOW_TIDE,
    MEDIUM_TIDE,
    HIGH_TIDE
};

class PackageDisplayCell : public QFrame
{
public:
    PackageDisplayCell();
    PackageDisplayCell(int ID, QString packageName, QString packageBannerPath, SportKindOnTide kind);

private:
    int _packageID;

    QLabel *_packageName;
    QLabel *_packageBanner;
//    QLabel *_packageDescription;  not going to include a description in such small view

    QPushButton *_bookButton;

    SportKindOnTide _compatibleTideKind;
};

#endif // PACKAGEDISPLAYCELL_H
