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
    title->setFixedHeight(200);
    mainLayout->addWidget(title);
    mainLayout->addStretch();

    QWidget *optionsContainer = new QWidget(this);
    QVBoxLayout *optionsLayout = new QVBoxLayout(optionsContainer);
    optionsLayout->setContentsMargins(20, 0, 20, 0);
    optionsContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    optionsLayout->setSpacing(15);
    QButtonGroup *radioGroup = new QButtonGroup();
    QFont optionFont("", 12, QFont::Medium);

    QFrame *line1 = new QFrame();
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);
    line1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    optionsLayout->addWidget(line1);

    QRadioButton *option1 = new QRadioButton("Erase disk and install Arch", this);
    option1->setFont(optionFont);
    radioGroup->addButton(option1, 1);
    optionsLayout->addWidget(option1);

    QFrame *line2 = new QFrame();
    line2->setFrameShape(QFrame::HLine);
    line2->setFrameShadow(QFrame::Sunken);
    line2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    optionsLayout->addWidget(line2);

    QRadioButton *option2 = new QRadioButton("Install Arch alongside your OS", this);
    option2->setFont(optionFont);
    radioGroup->addButton(option2, 2);
    optionsLayout->addWidget(option2);

    QFrame *line3 = new QFrame();
    line3->setFrameShape(QFrame::HLine);
    line3->setFrameShadow(QFrame::Sunken);
    line3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    optionsLayout->addWidget(line3);

    QRadioButton *option3 = new QRadioButton("Manual Installation", this);
    option3->setFont(optionFont);
    radioGroup->addButton(option3, 3);
    optionsLayout->addWidget(option3);

    QFrame *line4 = new QFrame();
    line4->setFrameShape(QFrame::HLine);
    line4->setFrameShadow(QFrame::Sunken);
    line4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    optionsLayout->addWidget(line4);

    optionsLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(optionsContainer);
    mainLayout->addStretch();

    connect(radioGroup, &QButtonGroup::idToggled, this, [=](int index) {
        if (!params.isEmpty()) {
            params[0] = QString::number(index);
        } else {
            params.append(QString::number(index));
        }
    });

    option1->toggle();
}
