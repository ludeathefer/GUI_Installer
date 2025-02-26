#include "installing.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QFont>

Installing::Installing(QStackedWidget *parent)
    : Page(parent)
{
    loadUi();
}

void Installing::loadUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Installing Radarch");
    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignHCenter);
    title->setFixedHeight(100);
    mainLayout->addWidget(title);

    mainLayout->addWidget(createDivider());
    mainLayout->addStretch();

    QLabel *description = new QLabel("Radarch is installing. Please wait until it completes. System will reboot automatically once the installation completes.");
    QFont descriptionFont;
    descriptionFont.setPointSize(12);
    description->setAlignment(Qt::AlignHCenter);
    description->setFont(descriptionFont);
    mainLayout->addWidget(description);
    description->setWordWrap(true);
    description->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    description->setMaximumWidth(300);
    mainLayout->addWidget(description, 0, Qt::AlignHCenter);

    mainLayout->addStretch();
}
