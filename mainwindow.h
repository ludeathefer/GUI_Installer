#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "console.h"
#include <QMainWindow>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
    Console *console;

    void maximizeWindow();
    void loadUi();

private slots:
    void onNextClick();
    void onBackClick();
    void onCancelClick();
};
#endif // MAINWINDOW_H
