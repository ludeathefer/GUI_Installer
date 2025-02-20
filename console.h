#ifndef CONSOLE_H
#define CONSOLE_H

#include <QWidget>
#include <QLabel>

class Console : public QWidget
{
    Q_OBJECT
public:
    explicit Console(QWidget *parent = nullptr);
    ~Console();

public slots:
    void onPageChange(int currentPageIndex);

private:
    QString scriptPath;
    QLabel *scriptOutput;
    void loadUi();
    void extractScript();
    void deleteScript();
};

#endif // CONSOLE_H
