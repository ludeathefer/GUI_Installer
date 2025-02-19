#include "installationtype.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QFont>

InstallationType::InstallationType(QStackedWidget *parent) : QWidget(parent)
{
    loadUi();
}

void InstallationType::loadUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Choose the type of installation");
    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(title);
}
