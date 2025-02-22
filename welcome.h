#ifndef WELCOME_H
#define WELCOME_H

#include "page.h"
#include <QStackedWidget>
#include <QWidget>

class Welcome : public Page
{
    Q_OBJECT
public:
    explicit Welcome(QStackedWidget *parent = nullptr);
private:
    void loadUi();
};

#endif // WELCOME_H
