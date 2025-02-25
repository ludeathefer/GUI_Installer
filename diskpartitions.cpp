#include "diskpartitions.h"

#include <QTreeWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QFont>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QHeaderView>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>
#include <QInputDialog>
#include <QComboBox>
#include <QMessageBox>
#include <QSpinBox>

DiskPartitions::DiskPartitions(QStackedWidget *parent)
    : Page{parent}
{
    loadUi();
}

void DiskPartitions::loadUi()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QLabel *title = new QLabel("Disk Partitions");
    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignHCenter);
    title->setFixedHeight(100);
    mainLayout->addWidget(title);

    mainLayout->addWidget(createDivider());
    mainLayout->addStretch();

    partitionTable = new QTreeWidget(this);
    QStringList partitionTableHeaders = {"Partition", "Size", "Type", "FSType", "Mount point"};
    partitionTable->setColumnCount(5);
    partitionTable->setHeaderLabels(partitionTableHeaders);
    populatePartitions();

    mainLayout->addWidget(partitionTable);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addPartitionButton = new QPushButton("Add Partition");
    QPushButton *deletePartitionButton = new QPushButton("Delete Partition");
    QPushButton *shrinkPartitionButton = new QPushButton("Shrink Partition");
    QPushButton *unallocatePartitionButton = new QPushButton("Unallocate Partition");

    buttonLayout->addWidget(addPartitionButton);
    buttonLayout->addWidget(shrinkPartitionButton);
    buttonLayout->addWidget(unallocatePartitionButton);
    buttonLayout->addWidget(deletePartitionButton);

    mainLayout->addLayout(buttonLayout);

    params.resize(3);

    connect(addPartitionButton, &QPushButton::clicked, this, &DiskPartitions::addPartition);
    connect(deletePartitionButton, &QPushButton::clicked, this, &DiskPartitions::deletePartition);
    connect(shrinkPartitionButton, &QPushButton::clicked, this, &DiskPartitions::shrinkPartition);
    connect(unallocatePartitionButton,  &QPushButton::clicked, this, &DiskPartitions::unallocatePartition);

    mainLayout->addStretch();
}

void DiskPartitions::populatePartitions()
{
    QProcess process;
    process.start("lsblk", { "-f", "-b", "-o", "NAME,SIZE,TYPE,FSTYPE,MOUNTPOINT", "--json", "/dev/sda"});
    process.waitForFinished();

    QByteArray output = process.readAllStandardOutput();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(output);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray devices = jsonObj["blockdevices"].toArray();

    if (devices.isEmpty()) return;

    QJsonObject sda = devices.first().toObject();
    double totalSize = sda["size"].toDouble();
    double usedSize = 0.0;
    QTreeWidgetItem *parentItem = new QTreeWidgetItem(partitionTable);
    parentItem->setText(0, "/dev/sda");
    parentItem->setText(1, QString::number(sda["size"].toDouble() / (1024 * 1024)) + " MB");
    parentItem->setText(2, sda["type"].toString());
    parentItem->setText(3, sda["fstype"].toString());
    parentItem->setText(3, "");
    partitionTable->addTopLevelItem(parentItem);

    if (sda.contains("children"))
    {
        QJsonArray partitions = sda["children"].toArray();
        for (const QJsonValue &partition : partitions)
        {
            QJsonObject partObj = partition.toObject();
            QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
            usedSize += partObj["size"].toDouble();
            childItem->setText(0, "/dev/" + partObj["name"].toString());
            childItem->setText(1, QString::number(partObj["size"].toDouble() / (1024 * 1024)) + " MB");
            childItem->setText(2, partObj["type"].toString());
            childItem->setText(3, partObj["fstype"].toString());
            childItem->setText(4, partObj["mountpoint"].toString().isEmpty() ? "Not Mounted" : partObj["mountpoint"].toString());
            parentItem->addChild(childItem);
        }
    }

    availableSpace = (totalSize - usedSize) / (1024 * 1024);
    partitionTable->expandAll();
    partitionTable->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void DiskPartitions::addPartition(double availableSpace) {
    QDialog* dialog = new QDialog();
    dialog->setWindowTitle("Add Partition");

    QVBoxLayout* layout = new QVBoxLayout(dialog);

    // Size
    QHBoxLayout* sizeLayout = new QHBoxLayout();
    QLabel* sizeLabel = new QLabel("Size (in MB):", dialog);
    QSpinBox* sizeEdit = new QSpinBox(dialog);
    sizeEdit->setRange(1, availableSpace);
    sizeLayout->addWidget(sizeLabel);
    sizeLayout->addWidget(sizeEdit);
    layout->addLayout(sizeLayout);

    // Type
    QHBoxLayout* typeLayout = new QHBoxLayout();
    QLabel* typeLabel = new QLabel("FSType:", dialog);
    QComboBox* typeComboBox = new QComboBox(dialog);
    typeComboBox->addItems({"NTFS", "FAT32", "exFAT", "VFAT", "EXT4", "BTRFS", "XFS", "SWAP"});
    typeLayout->addWidget(typeLabel);
    typeLayout->addWidget(typeComboBox);
    layout->addLayout(typeLayout);

    QHBoxLayout* mountLayout = new QHBoxLayout();
    QLabel* mountLabel = new QLabel("Mount Point:", dialog);
    QLineEdit* mountEdit = new QLineEdit(dialog);
    mountLayout->addWidget(mountLabel);
    mountLayout->addWidget(mountEdit);
    layout->addLayout(mountLayout);

    // Buttons
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    QPushButton* okButton = new QPushButton("OK", dialog);
    QPushButton* cancelButton = new QPushButton("Cancel", dialog);
    buttonsLayout->addWidget(okButton);
    buttonsLayout->addWidget(cancelButton);
    layout->addLayout(buttonsLayout);

    dialog->setLayout(layout);

    connect(okButton, &QPushButton::clicked, dialog, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, dialog, &QDialog::reject);

    if (dialog->exec() == QDialog::Accepted) {
        // QLineEdit* nameEdit = dialog->findChild<QLineEdit*>("nameEdit");
        // QComboBox* typeComboBox = dialog->findChild<QComboBox*>("typeComboBox");
        // QLineEdit* mountEdit = dialog->findChild<QLineEdit*>("mountEdit");

        // QString name = nameEdit->text();
        QString fstype = typeComboBox->currentText();
        QString mountPoint = mountEdit->text();


        QString size = sizeEdit->text();

        if(size.isEmpty() ){
            QMessageBox::warning(this,  "Error", "Size cannot be empty");
            return;
        }

        if(mountPoint.isEmpty()){
            QMessageBox::warning(this,  "Error", "Mount Point cannot be empty");
            return;
        }
        params[0] = size;
        params[1] = fstype;
        params[2] = mountPoint;
        // QString type = typeComboBox->currentText();
        // QString mountPoint = mountEdit->text();
        // QTreeWidgetItem* newItem = new QTreeWidgetItem(partitionTable);
        // newItem->setText(0, name);
        // newItem->setText(1, "");  // Size can be set later if needed
        // newItem->setText(2, type);
        // newItem->setText(3, mountPoint);

        // partitionTable->addTopLevelItem(newItem);
    }

    delete dialog;
    qDebug()<<params;
}

void DiskPartitions::deletePartition()
{
    QTreeWidgetItem *selectedItem = partitionTable->currentItem();
    if (!selectedItem || selectedItem->parent() == nullptr) return;

    QString partitionName = selectedItem->text(0);
    int ret = QMessageBox::warning(this, "Delete Partition", "Are you sure you want to delete " + partitionName + "?", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        QMessageBox::information(this, "Deleted", partitionName + " deleted.");
    }
}

void DiskPartitions::shrinkPartition(){
    QTreeWidgetItem *selectedItem = partitionTable->currentItem();
    if (!selectedItem || selectedItem->parent() == nullptr) {
        QMessageBox::warning(this, "Error", "Please select a valid partition to shrink.");
        return;
    }

    QString partitionName = selectedItem->text(0);
    bool ok;
    int newSize = QInputDialog::getInt(this, "Shrink Partition",
                                       "Enter new size in MB:", 100, 1, 1000000, 1, &ok);
    if (!ok) return;

    // QProcess process;
    // QString command = QString("sudo parted %1 resizepart %2 %3MB")
    //                       .arg("/dev/sda")
    //                       .arg(partitionName)
    //                       .arg(newSize);

    // process.start("bash", QStringList() << "-c" << command);
    // process.waitForFinished();

    // if (process.exitCode() == 0) {
    //     QMessageBox::information(this, "Success", "Partition shrunk successfully.");
    //     populatePartitions(); // Refresh UI
    // } else {
    //     QMessageBox::critical(this, "Error", "Failed to shrink the partition.");
    // }
}

void DiskPartitions::unallocatePartition(){
    QTreeWidgetItem *selectedItem = partitionTable->currentItem();
    if (!selectedItem || selectedItem->parent() == nullptr) {
        QMessageBox::warning(this, "Error", "Please select a valid partition to unallocate.");
        return;
    }

    QString partitionName = selectedItem->text(0);
    int ret = QMessageBox::warning(this, "Unallocate Partition",
                                   "Are you sure you want to unallocate " + partitionName + "?",
                                   QMessageBox::Yes | QMessageBox::No);
    if (ret != QMessageBox::Yes) return;

    // QProcess process;
    // QString command = QString("sudo parted /dev/sda rm %1").arg(partitionName);

    // process.start("bash", QStringList() << "-c" << command);
    // process.waitForFinished();

    // if (process.exitCode() == 0) {
    //     QMessageBox::information(this, "Success", "Partition unallocated successfully.");
    //     populatePartitions(); // Refresh UI
    // } else {
    //     QMessageBox::critical(this, "Error", "Failed to unallocate the partition.");
    // }
}

