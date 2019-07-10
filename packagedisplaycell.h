#ifndef PACKAGEDISPLAYCELL_H
#define PACKAGEDISPLAYCELL_H

#include <QLabel>
#include <QString>

enum SportKindOnTide{
    LOW_TIDE,
    MEDIUM_TIDE,
    HIGH_TIDE
};

class PackageDisplayCell : public QWidget
{
public:
    PackageDisplayCell();
    PackageDisplayCell(int ID, QString packageName, QString packageBannerPath, QString packageDescription);

private:
    int _packageID;

    QLabel *_packageName;
    QLabel *_packageBanner;
    QLabel *_packageDescription;

    SportKindOnTide _compatibleTideKind;
};

#endif // PACKAGEDISPLAYCELL_H
