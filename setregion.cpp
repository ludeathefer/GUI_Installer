#include "setregion.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QFont>
#include <QComboBox>

SetRegion::SetRegion(QStackedWidget *parent)
    : Page{parent}
{
    loadUi();
}

void SetRegion::loadUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Select your region");
    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignHCenter);
    title->setFixedHeight(200);
    mainLayout->addWidget(title);
    mainLayout->addStretch();

    QFont labelFont("", 12, QFont::Medium);

    QWidget *regionSelectionContainer = new QWidget(this);
    QVBoxLayout *regionSelectionLayout = new QVBoxLayout(regionSelectionContainer);
    regionSelectionLayout->setSpacing(15);
    regionSelectionLayout->setContentsMargins(80, 0, 80, 0);
    regionSelectionContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    regionSelectionLayout->addWidget(createDivider());

    QHBoxLayout *locationSelectionLayout = new QHBoxLayout();
    QLabel *locationSelectionLabel = new QLabel("Select location: ");
    locationSelectionLabel->setFont(labelFont);
    locationSelectionLayout->addWidget(locationSelectionLabel);
    QComboBox *locationSelection = new QComboBox(regionSelectionContainer);
    QStringList locationSelectionOptions = {"US ", "Nepal"};
    locationSelection->addItems(locationSelectionOptions);
    locationSelectionLayout->addWidget(locationSelection);
    regionSelectionLayout->addLayout(locationSelectionLayout);

    regionSelectionLayout->addWidget(createDivider());

    QHBoxLayout *timezoneSelectionLayout = new QHBoxLayout();
    QLabel *timezoneSelectionLabel = new QLabel("Select timezone: ");
    timezoneSelectionLabel->setFont(labelFont);
    timezoneSelectionLayout->addWidget(timezoneSelectionLabel);
    QComboBox *timezoneSelection = new QComboBox(regionSelectionContainer);
    QStringList  timezoneSelectionOptions = {"US (GMT - 05 : 00)", "Nepal (GMT + 05 : 45)"};
    timezoneSelection->addItems(timezoneSelectionOptions);
    timezoneSelectionLayout->addWidget(timezoneSelection);
    regionSelectionLayout->addLayout(timezoneSelectionLayout);

    regionSelectionLayout->addWidget(createDivider());

    mainLayout->addWidget(regionSelectionContainer);
    mainLayout->addStretch();
}
