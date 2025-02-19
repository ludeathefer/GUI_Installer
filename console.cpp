#include "console.h"

#include <QPalette>
#include <QVBoxLayout>
#include <QLabel>

Console::Console(QWidget *parent)
    : QWidget(parent)
{
    loadUi();
}

void Console::loadUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QPalette palette = QPalette();
    palette.setColor(QPalette::Window, Qt::black);

    setAutoFillBackground(true);
    setPalette(palette);

    QLabel *label = new QLabel("Console Output", this);
    QPalette labelPalette = QPalette(Qt::white);
    label->setPalette(labelPalette);
    mainLayout->addWidget(label);
}
