#include "installationoption.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QRadioButton>
#include <QButtonGroup>

InstallationOption::InstallationOption(QStackedWidget *parent)
    : Page{parent}
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
    title->setFixedHeight(100);
    mainLayout->addWidget(title);

    mainLayout->addWidget(createDivider());
    mainLayout->addStretch();

    QWidget *optionsContainer = new QWidget(this);
    QVBoxLayout *optionsLayout = new QVBoxLayout(optionsContainer);
    optionsLayout->setContentsMargins(20, 0, 20, 0);
    optionsContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    optionsLayout->setSpacing(15);
    QButtonGroup *radioGroup = new QButtonGroup();
    QFont optionFont("", 12, QFont::Medium);

    optionsLayout->addWidget(createDivider());

    QRadioButton *option1 = new QRadioButton("Automatic Installation", this);
    option1->setFont(optionFont);
    radioGroup->addButton(option1, 1);
    optionsLayout->addWidget(option1);

    optionsLayout->addWidget(createDivider());

    QRadioButton *option2 = new QRadioButton("Manual Installation", this);
    option2->setFont(optionFont);
    radioGroup->addButton(option2, 2);
    optionsLayout->addWidget(option2);

    optionsLayout->addWidget(createDivider());

    optionsLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(optionsContainer);
    mainLayout->addStretch();

    params.resize(1);
    connect(radioGroup, &QButtonGroup::idToggled, this, [=](int index) { params[0] = QString::number(index); });
    option1->toggle();
}
