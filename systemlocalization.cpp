#include "systemlocalization.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QFont>
#include <QComboBox>
#include <QFile>
#include <QDir>

SystemLocalization::SystemLocalization(QStackedWidget *parent)
    : Page{parent}
{
    loadUi();
}

void SystemLocalization::loadUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *title = new QLabel("System Localization");
    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignHCenter);
    title->setFixedHeight(100);
    mainLayout->addWidget(title);

    mainLayout->addWidget(createDivider());
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

    QStringList locations = getLocations();
    locationSelection->addItems(locations);

    locationSelectionLayout->addWidget(locationSelection);
    regionSelectionLayout->addLayout(locationSelectionLayout);

    regionSelectionLayout->addWidget(createDivider());

    QHBoxLayout *timezoneSelectionLayout = new QHBoxLayout();
    QLabel *timezoneSelectionLabel = new QLabel("Select timezone: ");
    timezoneSelectionLabel->setFont(labelFont);
    timezoneSelectionLayout->addWidget(timezoneSelectionLabel);
    QComboBox *timezoneSelection = new QComboBox(regionSelectionContainer);

    locationSelection->setCurrentIndex(0);
    QStringList timezones = getTimezones(locationSelection->currentText());
    timezoneSelection->addItems(timezones);

    timezoneSelectionLayout->addWidget(timezoneSelection);
    regionSelectionLayout->addLayout(timezoneSelectionLayout);

    regionSelectionLayout->addWidget(createDivider());

    mainLayout->addWidget(regionSelectionContainer);
    mainLayout->addStretch();

    connect(locationSelection, &QComboBox::currentTextChanged, this, [=](const QString &region) {
        timezoneSelection->clear();
        timezoneSelection->addItems(getTimezones(region));
    });

    locationSelection->setCurrentText("Asia");
    timezoneSelection->setCurrentText("Asia/Kathmandu");
}

QStringList SystemLocalization::getLocations()
{
    QStringList regions;
    QDir zoneDir("/usr/share/zoneinfo/");
    QStringList entries = zoneDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    for (const QString &entry : entries) {
        if (entry != "posix" && entry != "right" && entry != "SystemV" && entry != "Etc") {
            regions.append(entry);
        }
    }
    return regions;
}

QStringList SystemLocalization::getTimezones(const QString &region)
{
    QStringList timezones;
    QDir regionDir("/usr/share/zoneinfo/" + region);
    QStringList entries = regionDir.entryList(QDir::Files);

    for (const QString &entry : entries) {
        timezones.append(region + "/" + entry);
    }
    return timezones;
}
