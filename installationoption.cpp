#include "installationoption.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

InstallationOption::InstallationOption(QStackedWidget *parent)
    : QWidget{parent}
{
    loadUi();
}

void InstallationOption::loadUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Choose installation option");
    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(title);
}
