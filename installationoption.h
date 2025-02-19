#ifndef INSTALLATIONOPTION_H
#define INSTALLATIONOPTION_H

#include <QWidget>
#include <QStackedWidget>

class InstallationOption : public QWidget
{
    Q_OBJECT
public:
    explicit InstallationOption(QStackedWidget *parent = nullptr);

private:
    void loadUi();
};

#endif // INSTALLATIONOPTION_H
