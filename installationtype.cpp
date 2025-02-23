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
    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignHCenter);
    title->setFixedHeight(200);
    mainLayout->addWidget(title);
    mainLayout->addStretch();

    QWidget *itSelectionContainer = new QWidget(this);
    QHBoxLayout *itSelectionLayout= new QHBoxLayout(itSelectionContainer);
    itSelectionLayout->setContentsMargins(80, 0, 80, 0);
    itSelectionContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    QLabel *itLabel = new QLabel("Installation Type: ");
    QFont itLabelFont("", 12, QFont::Medium);
    itLabel->setFont(itLabelFont);
    itSelectionLayout->addWidget(itLabel);

    QComboBox *itSelection = new QComboBox(itSelectionContainer);
    QStringList itSelectionOptions = {"Minimal Installation", "Normal Installation (GUI)", "Normal Installation with added utilities"};

    itSelectionLayout->addWidget(itSelection);

    mainLayout->addWidget(itSelectionContainer);
    mainLayout->addStretch();

    params.resize(1);
    connect(itSelection, &QComboBox::currentIndexChanged, this, [=](int index) { params[0] = QString::number(index + 1); });
    itSelection->addItems(itSelectionOptions);
}

