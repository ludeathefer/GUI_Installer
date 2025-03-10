#include "console.h"

#include <QPalette>
#include <QVBoxLayout>
#include <QLabel>
#include <QTemporaryFile>
#include <QFile>
#include <QProcess>
#include <QDebug>
#include <QScrollBar>

Console::Console(QWidget *parent)
    : QWidget(parent)
{
    loadUi();
    extractScript();
}

Console::~Console()
{
    deleteScript();
}

void Console::loadUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QPalette palette = QPalette();
    palette.setColor(QPalette::Window, QColor(20, 20, 20, 1));
    setAutoFillBackground(true);
    setPalette(palette);

    QLabel *title = new QLabel("Console Output:");
    scriptOutput = new QLabel();
    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    QPalette textPalette = QPalette();
    textPalette.setColor(QPalette::WindowText, Qt::white);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignHCenter);
    title->setFixedHeight(100);
    title->setPalette(textPalette);
    mainLayout->addWidget(title);

    QFrame *line1 = new QFrame();
    line1->setFrameShape(QFrame::HLine);
    line1->setFrameShadow(QFrame::Sunken);
    line1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mainLayout->addWidget(line1);;
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setPalette(palette);

    scriptOutput = new QLabel();
    scriptOutput->setWordWrap(true);
    scriptOutput->setTextInteractionFlags(Qt::TextSelectableByMouse);
    scriptOutput->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    QPalette outputPalette;
    outputPalette.setColor(QPalette::WindowText, Qt::white);
    scriptOutput->setPalette(outputPalette);

    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->addWidget(scriptOutput);
    scrollLayout->addStretch();

    scrollArea->setWidget(scrollWidget);

    mainLayout->addWidget(scrollArea);
}

void Console::extractScript()
{
    QString scriptResourcePath = ":/script/installationscript.sh";
    QFile scriptFile(scriptResourcePath);

    if (!scriptFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open script file:" << scriptFile.errorString();
        return;
    }

    QTemporaryFile tempScript;
    if (!tempScript.open()) {
        qDebug() << "Failed to create temporary file";
        return;
    }
    tempScript.setAutoRemove(false);

    QTextStream out(&tempScript);
    out << scriptFile.readAll();
    tempScript.close();
    scriptFile.close();

    scriptPath = tempScript.fileName();
    QFile::setPermissions(scriptPath, QFileDevice::ExeOwner | QFileDevice::ReadOwner | QFileDevice::WriteOwner);
}

void Console::onExecuteScript(int currentPageIndex, QStringList params, QProcess *process)
{
    connect(process, &QProcess::readyReadStandardOutput, [=]() {
        QString output = process->readAllStandardOutput();
        QString formattedOutput = "<span style='color:white;'>$ : " + output + "</span><br><br>";
        scriptOutput->setText(scriptOutput->text() + formattedOutput);

        QScrollBar *scrollBar = scrollArea->verticalScrollBar();
        scrollBar->setValue(scrollBar->maximum());
    });

    connect(process, &QProcess::readyReadStandardError, [=]() {
        QString errorOutput = process->readAllStandardError();
        QString formattedError = "<span style='color:red;'>Error: " + errorOutput + "</span><br><br>";
        scriptOutput->setText(scriptOutput->text() + formattedError);

        QScrollBar *scrollBar = scrollArea->verticalScrollBar();
        scrollBar->setValue(scrollBar->maximum());
    });

    process->setProgram("/bin/bash");
    process->setArguments(QStringList() << scriptPath << QString::number(currentPageIndex) << params);

    process->start();
}

void Console::deleteScript()
{
    QFile::remove(scriptPath);
}

