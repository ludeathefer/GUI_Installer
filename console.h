#ifndef CONSOLE_H
#define CONSOLE_H

#include <QWidget>

class Console : public QWidget
{
    Q_OBJECT
public:
    explicit Console(QWidget *parent = nullptr);

private:
    void loadUi();

signals:
};

#endif // CONSOLE_H
