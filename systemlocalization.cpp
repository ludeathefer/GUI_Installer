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

    QHBoxLayout *localeSelectionLayout = new QHBoxLayout();
    QLabel *localeSelectionLabel = new QLabel("Select locale: ");
    localeSelectionLabel->setFont(labelFont);
    localeSelectionLayout->addWidget(localeSelectionLabel);
    QComboBox *localeSelection = new QComboBox(regionSelectionContainer);

    QHash<QString, QString> localeMap = getLocales();
    QStringList localeNames = localeMap.keys(); // Get display names
    localeSelection->addItems(localeNames);

    localeSelectionLayout->addWidget(localeSelection);
    regionSelectionLayout->addLayout(localeSelectionLayout);
    regionSelectionLayout->addWidget(createDivider());

    mainLayout->addWidget(regionSelectionContainer);
    mainLayout->addStretch();

    params.resize(3);;
    connect(locationSelection, &QComboBox::currentTextChanged, this, [=](const QString &region) {
        timezoneSelection->clear();
        timezoneSelection->addItems(getTimezones(region));
        params[0] = region;
    });

    connect(timezoneSelection, &QComboBox::currentTextChanged, this, [=](const QString &timezone) {
        params[1] = timezone;
    });

    connect(localeSelection, &QComboBox::currentTextChanged, this, [=](const QString &locale) {
        params[2] = localeMap.value(locale);
    });

    locationSelection->setCurrentText("Asia");
    timezoneSelection->setCurrentText("Asia/Kathmandu");
    localeSelection->setCurrentText("English (United States)");
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

QHash<QString, QString> SystemLocalization::getLocales()
{
    QHash<QString, QString> localeMap;
    QList<QLocale> locales = QLocale::matchingLocales(QLocale::AnyLanguage, QLocale::AnyScript, QLocale::AnyCountry);

    for (const QLocale &locale : locales) {
        QString displayName = QLocale::languageToString(locale.language()) + " (" + QLocale::territoryToString(locale.territory()) + ")";
        QString localeCode = locale.name() + ".UTF-8 UTF-8";
        localeMap.insert(displayName, localeCode);
    }

    return localeMap;
}
