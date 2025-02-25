#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "console.h"
#include "page.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QQueue>
#include <QStringList>
#include <QPushButton>

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
    QPushButton *next, *back, *cancel;
    Console *console;
    Page *currentPage;
    QList<QStringList> paramsStore;
    bool runningScript;

    void maximizeWindow();
    void loadUi();
    void executeScript(QStringList params);
    void closeEvent(QCloseEvent *event);

private slots:
    void onNextClick();
    void onBackClick();
    void onCancelClick();
};
#endif // MAINWINDOW_H
