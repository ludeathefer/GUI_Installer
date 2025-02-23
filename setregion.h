#ifndef SETREGION_H
#define SETREGION_H

#include "page.h"

class SetRegion : public Page
{
    Q_OBJECT
public:
    SetRegion(QStackedWidget *parent = nullptr);
private:
    void loadUi();
};

#endif // SETREGION_H
