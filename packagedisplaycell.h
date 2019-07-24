#ifndef PACKAGEDISPLAYCELL_H
#define PACKAGEDISPLAYCELL_H

#include <QLabel>
#include <QString>
#include <QPushButton>

class PackageDisplayCell : public QFrame
{
    Q_OBJECT

public:
    PackageDisplayCell();
    PackageDisplayCell(int ID, QString packageName, QString packageBannerPath);
    int ID() const;

signals:
    void clickedSignal();

private slots:
    void bookButtonClicked();
private:
    int _packageID;

    QLabel *_packageName;
    QLabel *_packageBanner;
//    QLabel *_packageDescription;  not going to include a description in such small view

    QPushButton *_bookButton;
};

#endif // PACKAGEDISPLAYCELL_H
