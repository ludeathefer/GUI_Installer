#ifndef WELCOME_H
#define WELCOME_H

#include <QStackedWidget>
#include <QWidget>

class Welcome : public QWidget
{
    Q_OBJECT
    public:
       explicit Welcome(QStackedWidget *parent = nullptr);

    private:
        void loadUi();
};

#endif // WELCOME_H
