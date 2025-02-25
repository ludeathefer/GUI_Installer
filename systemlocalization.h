#ifndef SYSTEMLOCALIZATION_H
#define SYSTEMLOCALIZATION_H

#include "page.h"

class SystemLocalization : public Page
{
    Q_OBJECT
public:
    SystemLocalization(QStackedWidget *parent = nullptr);
private:
    void loadUi();
    QStringList getLocations();
    QStringList getTimezones(const QString &region);
    QHash<QString, QString> getLocales();
};

#endif // SYSTEMLOCALIZATION_H
