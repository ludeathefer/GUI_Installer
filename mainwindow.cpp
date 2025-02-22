#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "page.h"
#include "welcome.h"
#include "installationoption.h"
#include "installationtype.h"
#include "createaccount.h"

#include <QWidget>
#include <QStackedWidget>
#include <QScreen>
#include <QGuiApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    maximizeWindow();
    loadUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::maximizeWindow()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect availableGeometry = screen->availableGeometry();
    setMinimumSize(availableGeometry.size());
    setMaximumSize(availableGeometry.size());
}

void MainWindow::loadUi()
{
    QHBoxLayout *mainLayout = new QHBoxLayout(ui->centralwidget);
    mainLayout->setContentsMargins(10, 0, 10, 10);
    mainLayout->setSpacing(10);

    int windowWidth = width();
    int halfWidth = (windowWidth - 10) / 2;

    QVBoxLayout *stackedWidgetLayout = new QVBoxLayout();
    stackedWidget = new QStackedWidget(ui->centralwidget);
    Welcome *welcome = new Welcome(stackedWidget);
    InstallationType *installationType = new InstallationType(stackedWidget);
    InstallationOption *installationOption = new InstallationOption(stackedWidget);
    CreateAccount *createAccount = new CreateAccount(stackedWidget);
    stackedWidget->addWidget(welcome);
    stackedWidget->addWidget(installationOption);
    stackedWidget->addWidget(installationType);
    stackedWidget->addWidget(createAccount);
    stackedWidgetLayout->addWidget(stackedWidget);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    QPushButton *next = new QPushButton("Next", this);
    connect(next, &QPushButton::clicked, this, &MainWindow::onNextClick);
    QPushButton *back = new QPushButton("Back", this);
    back->setEnabled(false);
    connect(back, &QPushButton::clicked, this, &MainWindow::onBackClick);
    QPushButton *cancel = new QPushButton("Cancel", this);
    connect(cancel, &QPushButton::clicked, this, &MainWindow::onCancelClick);
    buttonsLayout->addStretch(3);
    buttonsLayout->addWidget(back);
    buttonsLayout->addWidget(next);
    buttonsLayout->addWidget(cancel);

    connect(stackedWidget, &QStackedWidget::currentChanged, this, [=](int index) {
        back->setEnabled(index > 0);

        int maxIndex = stackedWidget->count() - 1;
        next->setText(index == maxIndex ? "Finish" : "Next");

        if (index > 0) {
            stackedWidget->setMaximumWidth(halfWidth);
            mainLayout->setStretch(0, 1);
            mainLayout->setStretch(1, 1);
        } else {
            stackedWidget->setMaximumWidth(windowWidth);
            mainLayout->setStretch(0, 0);
            mainLayout->setStretch(1, 0);
        }

        console->setVisible(index > 0);
    });
    stackedWidgetLayout->addLayout(buttonsLayout);

    QVBoxLayout *consoleLayout = new QVBoxLayout();
    console = new Console(ui->centralwidget);
    console->setVisible(false);
    console->setMaximumWidth(halfWidth);
    consoleLayout->addWidget(console);

    mainLayout->addLayout(stackedWidgetLayout);
    mainLayout->addLayout(consoleLayout);
}

void MainWindow::executeScript()
{
    int currentIndex = stackedWidget->currentIndex();
    Page *page = qobject_cast<Page*>(stackedWidget->currentWidget());
    qDebug() << page->params;
    console->onExecuteScript(currentIndex, page->params);
}

void MainWindow::onBackClick()
{
    executeScript();
    int currentIndex = stackedWidget->currentIndex();
    stackedWidget->setCurrentIndex(currentIndex - 1);
}

void MainWindow::onNextClick()
{
    executeScript();
    int currentIndex = stackedWidget->currentIndex();
    int maxIndex = stackedWidget->count() - 1;
    if(currentIndex != maxIndex)
        stackedWidget->setCurrentIndex(currentIndex + 1);
    else
        close();
}

void MainWindow::onCancelClick()
{
    close();
}
