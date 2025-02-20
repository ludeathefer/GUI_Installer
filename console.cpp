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
    titleFont.setPointSize(20);
    titleFont.setBold(true);

    QPalette textPalette = QPalette();
    textPalette.setColor(QPalette::WindowText, Qt::white);

    title->setFont(titleFont);
    title->setAlignment(Qt::AlignHCenter);
    title->setPalette(textPalette);

    mainLayout->addWidget(title);
    mainLayout->addWidget(scriptOutput);
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

void Console::onPageChange(int currentPageIndex)
{
    QProcess *process = new QProcess(this);
    connect(process, &QProcess::readyReadStandardOutput, [=]() {
        QByteArray output = process->readAllStandardOutput();
        scriptOutput->setText(output);
    });

    connect(process, &QProcess::readyReadStandardError, [=]() {
        QByteArray errorOutput = process->readAllStandardError();
        scriptOutput->setText("Error: " + errorOutput);
        QPalette errorPalette = QPalette();
        errorPalette.setColor(QPalette::WindowText, Qt::red);
        scriptOutput->setPalette(errorPalette);

    });

    process->setProgram("/bin/bash");
    process->setArguments(QStringList() << scriptPath << QString::number(currentPageIndex));

    process->start();
}

void Console::deleteScript()
{
    QFile::remove(scriptPath);
}
