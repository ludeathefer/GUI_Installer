#ifndef CONSOLE_H
#define CONSOLE_H

#include <QWidget>
#include <QLabel>
#include <QProcess>
#include <QScrollArea>

class Console : public QWidget
{
    Q_OBJECT
public:
    explicit Console(QWidget *parent = nullptr);
    ~Console();
    void onExecuteScript(int currentPageIndex, QStringList params, QProcess *process);

private:
    QString scriptPath;
    QLabel *scriptOutput;
    QScrollArea *scrollArea;

    void loadUi();
    void extractScript();
    void deleteScript();
};

#endif // CONSOLE_H
