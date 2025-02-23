#include "console.h"

#include <QPalette>
#include <QVBoxLayout>
#include <QLabel>
#include <QTemporaryFile>
#include <QFile>
#include <QProcess>
#include <QDebug>

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
    qDebug() << "Console Loaded.";
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QPalette palette = QPalette();
    palette.setColor(QPalette::Window, Qt::black);
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
    mainLayout->addStretch();

    mainLayout->addWidget(scriptOutput);

    mainLayout->addStretch();
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

void Console::onExecuteScript(int currentPageIndex, QStringList params)
{
    QProcess *process = new QProcess(this);
    connect(process, &QProcess::readyReadStandardOutput, [=]() {
        QString output = process->readAllStandardOutput();
        output.prepend(scriptOutput->text());
        scriptOutput->setText(output);
    });

    connect(process, &QProcess::readyReadStandardError, [=]() {
        QString errorOutput = process->readAllStandardError();
        scriptOutput->setText("Error: " + errorOutput);
        QPalette errorPalette = QPalette();
        errorPalette.setColor(QPalette::WindowText, Qt::red);
        scriptOutput->setPalette(errorPalette);

    });

    process->setProgram("/bin/bash");
    process->setArguments(QStringList() << scriptPath << QString::number(currentPageIndex) << params);

    process->start();
}

void Console::deleteScript()
{
    QFile::remove(scriptPath);
}

