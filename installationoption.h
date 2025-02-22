#ifndef INSTALLATIONOPTION_H
#define INSTALLATIONOPTION_H

#include "page.h"
#include <QStackedWidget>

class InstallationOption : public Page
{
    Q_OBJECT
public:
    explicit InstallationOption(QStackedWidget *parent = nullptr);
private:
    void loadUi();

};

#endif // INSTALLATIONOPTION_H
