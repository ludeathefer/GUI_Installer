#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QRandomGenerator>
#include <QProcess>
#include <QRegularExpression>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QString>
#include <QWidget>
#include <QStack>


void populatePartitionTree(QTreeWidget *treeWidget, QString disk) {
    treeWidget->clear();  // Clear existing entries

    QProcess process;
    process.start(QString("lsblk -o NAME,SIZE,FSTYPE,MOUNTPOINT /dev/%1").arg(disk));
    process.waitForFinished();
    QStringList lines = QString(process.readAllStandardOutput()).split("\n");

    QTreeWidgetItem *diskItem = new QTreeWidgetItem(treeWidget);
    diskItem->setText(0, disk);
    treeWidget->addTopLevelItem(diskItem);

    for (const QString &line : lines) {
        QStringList cols = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        if (cols.size() < 2 || !cols[0].contains(disk)) continue;

        QTreeWidgetItem *partitionItem = new QTreeWidgetItem(diskItem);
        partitionItem->setText(0, "/dev/" + cols[0]);
        partitionItem->setText(1, cols[1]);  // Size
        partitionItem->setText(2, cols.value(2, "-"));  // Type
        partitionItem->setText(3, cols.value(3, "-"));  // Mount Point
    }


    treeWidget->expandAll();  // Expand tree for visibility
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ArchLinuxInstaller)
{
    ui->setupUi(this);
    // SecondPage = new QWidget();
    // SecondPage->setStyleSheet("background-color: lightblue;");  // Example styling
    // SecondPage = ;
    // // Add secondPage to stackedWidget
    // SecondPage =
    // ui->stackedWidget->setCurrentIndex(2)
    //toolbutton 8, 11, 14
    //lineEdit, lineEdit_1, 2, 3, 4,5
    ui->toolButton_8->setEnabled(false);
    ui->toolButton_11->setEnabled(false);
    ui->toolButton_14->setEnabled(false);
    ui->toolButton_14->setEnabled(false);
    ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    ui->lineEdit_5->setEchoMode(QLineEdit::Password);

    connect(ui->radioButton, &QRadioButton::toggled, this, &MainWindow::checkDiskOption);
    connect(ui->radioButton_2, &QRadioButton::toggled, this, &MainWindow::checkDiskOption);
    connect(ui->radioButton_3, &QRadioButton::toggled, this, &MainWindow::checkDiskOption);

    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::checkAccount);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &MainWindow::generateComputerName);
    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, &MainWindow::checkAccount);
    connect(ui->lineEdit_3, &QLineEdit::textChanged, this, &MainWindow::checkAccount);
    connect(ui->lineEdit_4, &QLineEdit::textChanged, this, &MainWindow::checkAccount);
    connect(ui->lineEdit_5, &QLineEdit::textChanged, this, &MainWindow::checkAccount);
    connect(ui->lineEdit_4, &QLineEdit::textChanged, this, &MainWindow::checkPasswordMatch);
    connect(ui->lineEdit_5, &QLineEdit::textChanged, this, &MainWindow::checkPasswordMatch);
    // connect(ui->radioButton_4, &QRadioButton::toggled, this, &MainWindow::checkAccount);
   // connect(ui->comboBox, &QComboBox::currentTextChanged, this, &MainWindow::installationSelectedUpdateTerminal);

    connect(ui->radioButton_5, &QRadioButton::toggled, this, &MainWindow::checkAgreed);

    populatePartitionTree(ui->treeWidget, "sda");

    // commandWindow = new QTextEdit();
    // commandWindow->setReadOnly(true);
    // commandWindow->resize(600, 400);
    // commandWindow->show();
    script << "GUI_Installer/build/abc.sh";
    consolePage = ui->page_7;
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_4);
}


void MainWindow::on_toolButton_3_clicked()
{
    MainWindow::~MainWindow();
}


void MainWindow::on_toolButton_4_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

    QStringList args;


void MainWindow::on_toolButton_6_clicked()
{

    if(ui->comboBox->currentText() == "Normal Installation with a GUI")
    {
        //GUI wala script
        script << "Normal GUI haalxa rey!";
    }
    else if(ui->comboBox->currentText() == "Normal Installation with a GUI and some Utilities")
    {
        //GUI ra bloatware wala script
        script << "Bloatwares pani haalxa rey!";
    }
    else
    {
        //Minimal installation ko script
        script << "GUI nai chaidaina rey rey!";
    }

    // ui->stackedWidget->setCurrentWidget(ui->page_5);
    qDebug() << "Aba chalxa!";
    QProcess *process = new QProcess(this);

    connect(process, &QProcess::readyReadStandardOutput, [process, this]() {
        qDebug() << qPrintable(process->readAllStandardOutput());
        ui->textEdit_2->setText(process->readAllStandardOutput());
    });

    process->start("bash", script);
    ui->stackedWidget->setCurrentWidget(ui->page_5);



}


void MainWindow::on_toolButton_5_clicked()
{
    MainWindow::~MainWindow();
}


void MainWindow::on_toolButton_7_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_4);
}


void MainWindow::on_toolButton_8_clicked()
{
    //if manual installation then go ta a different screen, else go to ui->page
    if( ui->radioButton_3->isChecked() ){
        //Manual installation wala script
        ui->stackedWidget->setCurrentWidget(ui->page_6);
    }
    else if(ui->radioButton->isChecked()){
        //Existing OS sangai halne script
        ui->stackedWidget->setCurrentWidget(ui->page);
    }
    else
    {
        //Erase garera haalne script
        ui->stackedWidget->setCurrentWidget(ui->page);
    }
}


void MainWindow::on_toolButton_9_clicked()
{
    MainWindow::~MainWindow();
}
void MainWindow::on_toolButton_10_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_5);
}


void MainWindow::on_toolButton_11_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
    MainWindow::saveUserInfo(ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text(), ui->lineEdit_4->text(), ui->radioButton_4->isChecked());
}


void MainWindow::on_toolButton_12_clicked()
{
    MainWindow::~MainWindow();
}


void MainWindow::on_plainTextEdit_blockCountChanged(int newBlockCount)
{

}


void MainWindow::on_toolButton_13_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}



void MainWindow::on_toolButton_14_clicked()
{
    //Install Pressed
    //install hune script run garne aba
    //ani installing wala screen dekhaune?
}


void MainWindow::on_toolButton_15_clicked()
{
    MainWindow::~MainWindow();
}




void MainWindow::on_radioButton_toggled(bool checked)
{

}

void MainWindow::checkDiskOption()
{
    if( ui->radioButton->isChecked() || ui->radioButton_2->isChecked() || ui->radioButton_3->isChecked() )
        ui->toolButton_8->setEnabled(true);
    else
        ui->toolButton_8->setEnabled(false);
    // if(ui->lineEdit->)
}

void MainWindow::checkAccount()
{
    if( ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty() || ui->lineEdit_3->text().isEmpty() || ui->lineEdit_4->text().isEmpty() || ui->lineEdit_5->text().isEmpty() && ui->lineEdit_4->text()==ui->lineEdit_5->text() )
        ui->toolButton_11->setEnabled(false);
    else
        ui->toolButton_11->setEnabled(true);
}

void MainWindow::checkAgreed()
{
    if( ui->radioButton_5->isChecked() )
        ui->toolButton_14->setEnabled(true);
    else
        ui->toolButton_14->setEnabled(false);
}

void MainWindow::generateComputerName()
{
    QString name = ui->lineEdit->text().trimmed();
    if (!name.isEmpty()) {
        QString sanitized = name.toLower().replace(" ", "");
        int randomNumber = QRandomGenerator::global()->bounded(1000, 9999);
        ui->lineEdit_2->setText(sanitized + "-" + QString::number(randomNumber));
    }
}

void MainWindow::checkPasswordMatch()
{
    QString password = ui->lineEdit_4->text();
    QString reenterPassword = ui->lineEdit_5->text();

    // Password must be at least 6 characters
    if (password.length() < 6 && password.length() != 0) {
        ui->label_password->setText("Password must be at least 6 characters.");
        ui->label_password->setStyleSheet("color: red;");
    } else {
        ui->label_password->clear();
    }

    // Ensure passwords match
    if (!reenterPassword.isEmpty() && password != reenterPassword) {
        ui->label_re_password->setText("Passwords do not match.");
        ui->label_re_password->setStyleSheet("color: red;");
    } else {
        ui->label_re_password->clear();
    }

}


void MainWindow::on_toolButton_19_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_5);
}


void MainWindow::on_toolButton_20_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}


void MainWindow::on_toolButton_21_clicked()
{
    MainWindow::~MainWindow();
}



void MainWindow::saveUserInfo(const QString &name, const QString &computerName,
                  const QString &username, const QString &password, const bool &remember) {
    QJsonObject userInfo;
    userInfo["name"] = name;
    userInfo["computerName"] = computerName;
    userInfo["username"] = username;
    userInfo["password"] = password;
    userInfo["requirePassword"] = remember;

    // Convert JSON to string
    QJsonDocument doc(userInfo);
    QByteArray jsonData = doc.toJson();

    // Write to a file
    QFile file("user_info.json");
    if (file.open(QIODevice::Append)) {
        file.write(jsonData);
        file.close();
        qDebug() << "User info saved successfully!";
    } else {
        qDebug() << "Failed to save user info!";
    }
}

// void MainWindow::installationSelectedUpdateTerminal(){
//     if(ui->comboBox->currentText() == "Normal Installation with a GUI")
//     {
//         //GUI wala script
//         ui->textEdit->setText("pacman -S base xorg plasma");
//     }
//     else if(ui->comboBox->currentText() == "Normal Installation with a GUI and some Utilities")
//     {
//         //GUI ra bloatware wala script
//         ui->textEdit->setText("pacman -S base xorg plasma kde-applications");
//     }
//     else
//     {
//         //Minimal installation ko script
//         ui->textEdit->setText("pacman -S base");
//     }
// }

void MainWindow::on_toolButton_24_clicked()//console ko back
{
    ui->textEdit_2->clear();
    if (!pageHistory.isEmpty()) {
        QWidget* previousPage = pageHistory.pop();
        ui->stackedWidget->setCurrentWidget(previousPage);
    }
}


void MainWindow::on_toolButton_23_clicked()
{
    //Time zone ko
    ui->textEdit_2->setText("hello \n Hello");
    QWidget* currentWidget = ui->stackedWidget->currentWidget();
    if (currentWidget != consolePage) {
        pageHistory.push(currentWidget);
        ui->stackedWidget->setCurrentWidget(consolePage);
    }
}


void MainWindow::on_toolButton_22_clicked()
{
    //Create account ko console
    QWidget* currentWidget = ui->stackedWidget->currentWidget();
    if (currentWidget != consolePage) {
        pageHistory.push(currentWidget);
        ui->stackedWidget->setCurrentWidget(consolePage);
    }
}


void MainWindow::on_toolButton_18_clicked()
{
    //Partition ko console
    QWidget* currentWidget = ui->stackedWidget->currentWidget();
    if (currentWidget != consolePage) {
        pageHistory.push(currentWidget);
        ui->stackedWidget->setCurrentWidget(consolePage);
    }
}


void MainWindow::on_toolButton_17_clicked()
{
    //How do you want to install arch ko console
    QWidget* currentWidget = ui->stackedWidget->currentWidget();
    if (currentWidget != consolePage) {
        pageHistory.push(currentWidget);
        ui->stackedWidget->setCurrentWidget(consolePage);
    }
}


void MainWindow::on_toolButton_16_clicked()
{
    //Type of installation ko cosole
    if(ui->comboBox->currentText() == "Normal Installation with a GUI")
    {
        //GUI wala script
        ui->textEdit_2->setText("pacman -S base xorg plasma");
    }
    else if(ui->comboBox->currentText() == "Normal Installation with a GUI and some Utilities")
    {
        //GUI ra bloatware wala script
        ui->textEdit_2->setText("pacman -S base xorg plasma kde-applications");
    }
    else
    {
        //Minimal installation ko script
        ui->textEdit_2->setText("pacman -S base");
    }
    QWidget* currentWidget = ui->stackedWidget->currentWidget();
    if (currentWidget != consolePage) {
        pageHistory.push(currentWidget);
        ui->stackedWidget->setCurrentWidget(consolePage);
    }

}

