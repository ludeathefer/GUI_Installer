#ifndef INSTALLING_H
#define INSTALLING_H

#include "page.h"

class Installing : public Page
{
    Q_OBJECT
public:
    Installing(QStackedWidget *parent = nullptr);
private:
    void loadUi();
};

#endif // INSTALLING_H
