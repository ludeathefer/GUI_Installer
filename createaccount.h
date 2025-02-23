#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H

#include "page.h"

class CreateAccount : public Page
{
public:
    explicit CreateAccount(QStackedWidget *parent = nullptr);
private:
    void loadUi();
};

#endif // CREATEACCOUNT_H
