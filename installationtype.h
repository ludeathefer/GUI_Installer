#ifndef INSTALLATIONTYPE_H
#define INSTALLATIONTYPE_H

#include "page.h"
#include <QStackedWidget>

class InstallationType: public Page
{
    Q_OBJECT
public:
    explicit InstallationType(QStackedWidget *parent = nullptr);
private:
    void loadUi();
};

#endif // INSTALLATIONTYPE_H
