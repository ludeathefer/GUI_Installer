#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "console.h"
#include "page.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QQueue>
#include <QStringList>

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
signals:
    void nextClicked();

private:
    Ui::MainWindow *ui;
    QStackedWidget *stackedWidget;
    Console *console;
    Page *currentPage;

    void maximizeWindow();
    void loadUi();
    void executeScript();
    void closeEvent(QCloseEvent *event);

private slots:
    void onNextClick();
    void onBackClick();
    void onCancelClick();
};
#endif // MAINWINDOW_H
