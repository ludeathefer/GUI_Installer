#ifndef INSTALLATIONTYPE_H
#define INSTALLATIONTYPE_H

#include <QWidget>
#include <QStackedWidget>

class InstallationType: public QWidget
{
    Q_OBJECT
public:
    explicit InstallationType(QStackedWidget *parent = nullptr);

private:
    void loadUi();
};

#endif // INSTALLATIONTYPE_H
