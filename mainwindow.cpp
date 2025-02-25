#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "page.h"
#include "welcome.h"
#include "installationoption.h"
#include "installationtype.h"
#include "createaccount.h"
#include "systemlocalization.h"
#include "diskpartitions.h"
#include "installing.h"

#include <QWidget>
#include <QStackedWidget>
#include <QScreen>
#include <QGuiApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QCloseEvent>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    maximizeWindow();
    paramsStore.resize(6);
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
    SystemLocalization *systemLocalization = new SystemLocalization(stackedWidget);
    DiskPartitions *diskPartitions = new DiskPartitions(stackedWidget);
    Installing *installing = new Installing(stackedWidget);

    stackedWidget->addWidget(welcome);
    currentPage = qobject_cast<Page*>(stackedWidget->currentWidget());

    stackedWidget->addWidget(installationType);
    stackedWidget->addWidget(installationOption);

    stackedWidget->addWidget(diskPartitions);
    stackedWidget->addWidget(createAccount);

    stackedWidget->addWidget(systemLocalization);
    stackedWidget->addWidget(installing);
    stackedWidgetLayout->addWidget(stackedWidget);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    next = new QPushButton("Next", this);
    connect(next, &QPushButton::clicked, this, &MainWindow::onNextClick);
    back = new QPushButton("Back", this);
    back->setVisible(false);
    connect(back, &QPushButton::clicked, this, &MainWindow::onBackClick);
    cancel = new QPushButton("Cancel", this);
    connect(cancel, &QPushButton::clicked, this, &MainWindow::onCancelClick);
    buttonsLayout->addStretch(3);
    buttonsLayout->addWidget(back);
    buttonsLayout->addWidget(next);
    buttonsLayout->addWidget(cancel);

    QFrame *line1 = new QFrame();
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);
    line1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    stackedWidgetLayout->addWidget(line1);;
    stackedWidgetLayout->addLayout(buttonsLayout);

    QVBoxLayout *consoleLayout = new QVBoxLayout();
    console = new Console(ui->centralwidget);
    console->setVisible(false);
    console->setMaximumWidth(halfWidth);
    consoleLayout->addWidget(console);
\
    mainLayout->addLayout(consoleLayout);
    mainLayout->addLayout(stackedWidgetLayout);

    connect(stackedWidget, &QStackedWidget::currentChanged, this, [=](int index) {
        currentPage = qobject_cast<Page*>(stackedWidget->currentWidget());


        if (index == 4)
        {
            connect(this, &MainWindow::nextClicked, createAccount, &CreateAccount::validateFields);
            next->setEnabled(!currentPage->error);
            connect(currentPage, &Page::errorChanged, this, [=](bool changedError) {
                next->setEnabled(!changedError);
            });
        }

        int maxIndex = stackedWidget->count() - 1;
        next->setText(index == maxIndex ? "Finish" : "Next");


        back->setVisible(index > 0 && index != maxIndex);
        cancel->setVisible(index != maxIndex);

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
}

void MainWindow::executeScript(QStringList params)
{
    int currentIndex = stackedWidget->currentIndex();
    qDebug() << params;

    next->setEnabled(false);
    back->setEnabled(false);
    cancel->setEnabled(false);
    runningScript = true;

    QProcess *process = new QProcess(this);
    connect(process, &QProcess::finished, this, [=]() {
        next->setEnabled(true);
        back->setEnabled(true);
        cancel->setEnabled(true);
        runningScript = false;
        process->deleteLater();
    });

    console->onExecuteScript(currentIndex, params, process);
}

void MainWindow::onBackClick()
{
    int currentIndex = stackedWidget->currentIndex();
    disconnect(currentPage, &Page::errorChanged, nullptr, nullptr);
    stackedWidget->setCurrentIndex(currentIndex - (currentIndex == 4 ? 2: 1));
}

void MainWindow::onNextClick()
{
    int currentIndex = stackedWidget->currentIndex();
    int maxIndex = stackedWidget->count() - 1;

    emit nextClicked();
    if (currentPage->error)
        return;

    disconnect(currentPage, &Page::errorChanged, nullptr, nullptr);

    if (currentIndex < 6)
        paramsStore[currentIndex] = currentPage->params;

    if (currentIndex == 2 && currentPage->params.at(0) != "2") {
        executeScript(currentPage->params);
        stackedWidget->setCurrentIndex(currentIndex + 2);
    }
    else if (currentIndex == maxIndex - 1) {
        QStringList flattenedParams;
        for (const auto &paramList : paramsStore) {
            flattenedParams.append(paramList);
        }
        executeScript(flattenedParams);
        stackedWidget->setCurrentIndex(currentIndex + 1);
    }
    else if (currentIndex != maxIndex) {
        executeScript(currentPage->params);
        stackedWidget->setCurrentIndex(currentIndex + 1);
    }
    else {
        close();
    }
}

void MainWindow::onCancelClick()
{
    close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    int currentIndex = stackedWidget->currentIndex();
    int maxIndex = stackedWidget->count() - 1;

    if (currentIndex == maxIndex) {
        if (runningScript) {
        QMessageBox::warning(this, "Installation in progress", "Qutting while installation is in progess will lead to critical system errors. Please wait until it is completed.", QMessageBox::Ok);
        event->ignore();
        } else {
            event->accept();
        }
        return;
    };

    int ret = QMessageBox::warning(this, "Cancel Installation", "Are you sure you want to cancel? You will have to start over.", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        event->accept();
    } else
        event->ignore();
}
