#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui {
class ArchLinuxInstaller;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStringList script;


private slots:

    // void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    // void on_stackedWidget_currentChanged(int arg1);

    // void on_pushButton_clicked();

    void on_toolButton_3_clicked();

    void on_toolButton_4_clicked();

    void on_toolButton_6_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_7_clicked();

    void on_toolButton_8_clicked();

    void on_toolButton_9_clicked();

    void on_toolButton_10_clicked();

    void on_toolButton_11_clicked();

    void on_toolButton_12_clicked();

    void on_plainTextEdit_blockCountChanged(int newBlockCount);

    void on_toolButton_13_clicked();

    void on_toolButton_14_clicked();

    void on_toolButton_15_clicked();

    void on_radioButton_toggled(bool checked);

    void checkDiskOption();

    void checkAccount();

    void checkAgreed();

    void checkPasswordMatch();

    void generateComputerName();

    void on_toolButton_19_clicked();

    void on_toolButton_20_clicked();

    void on_toolButton_21_clicked();

    void saveUserInfo(const QString &name, const QString &computerName,
                      const QString &username, const QString &password, const bool &remember);

    void installationSelectedUpdateTerminal();

private:
    Ui::ArchLinuxInstaller *ui;
    QTextEdit *commandWindow;
    //QProcess *process;
    // QWidget *SecondPage;
};
#endif // MAINWINDOW_H
