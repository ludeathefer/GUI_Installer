#include "installationtype.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QFont>
#include <QComboBox>

InstallationType::InstallationType(QStackedWidget *parent)
    : Page{parent}
{
    loadUi();
}

void InstallationType::loadUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Choose the type of installation");
    QFont titleFont("", 20, QFont::Bold);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(title);

    QHBoxLayout *hBoxLayout = new QHBoxLayout();

    QLabel *itLabel = new QLabel("Installation Type: ");
    QFont itLabelFont("", 12, QFont::Medium);
    itLabel->setFont(itLabelFont);
    hBoxLayout->addWidget(itLabel);

    QComboBox *itSelection = new QComboBox(this);
    QStringList itSelectionOptions = {"Minimal Installation", "Normal Installation (GUI)", "Normal Installation with added utilities"};

    connect(itSelection, &QComboBox::currentIndexChanged, this, [=](int index) {
        if (!params.isEmpty()) {
            params[0] = QString::number(index + 1);
        } else {
            params.append(QString::number(index + 1));
        }
    });

    itSelection->addItems(itSelectionOptions);
    hBoxLayout->addWidget(itSelection);

    mainLayout->addLayout(hBoxLayout);
}

