#include "welcome.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

Welcome::Welcome(QStackedWidget *parent)
    : Page{parent}
{
    loadUi();
}

void Welcome::loadUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Welcome to the Radarch Linux Installation Wizard");
    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignHCenter);
    title->setFixedHeight(100);
    mainLayout->addWidget(title);

    mainLayout->addWidget(createDivider());
    mainLayout->addStretch();

    QLabel *description = new QLabel("This installer will guide you through the most difficult task of installing Arch Linux on your PC,\nand you wont feel it as hard as it used to be.");
    QFont descriptionFont;
    descriptionFont.setPointSize(14);
    description->setAlignment(Qt::AlignHCenter);
    description->setFont(descriptionFont);
    mainLayout->addWidget(description);
}
