#include "diskpartitions.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QProcess>
#include <QLabel>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QHeaderView>

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

    partitionTable = new QTreeWidget(this);
    QStringList partitionTableHeaders = {"Partition", "Size", "Type", "Mount Point"};
    partitionTable->setColumnCount(4);
    partitionTable->setHeaderLabels(partitionTableHeaders);
    populatePartitions();
    mainLayout->addWidget(partitionTable);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addPartitionButton = new QPushButton("Add Partition");
    QPushButton *deletePartitionButton = new QPushButton("Delete Partition");
    QPushButton *modifyPartitionButton = new QPushButton("Modify Partition");

    buttonLayout->addWidget(addPartitionButton);
    buttonLayout->addWidget(deletePartitionButton);
    buttonLayout->addWidget(modifyPartitionButton);
    mainLayout->addLayout(buttonLayout);

    connect(addPartitionButton, &QPushButton::clicked, this, &DiskPartitions::addPartition);
    connect(deletePartitionButton, &QPushButton::clicked, this, &DiskPartitions::deletePartition);
    connect(modifyPartitionButton, &QPushButton::clicked, this, &DiskPartitions::modifyPartition);
}

void DiskPartitions::populatePartitions()
{
    partitionTable->clear();
    QProcess process;
    process.start("lsblk", {"-b", "-o", "NAME,SIZE,TYPE,MOUNTPOINT", "--json", "/dev/sda"});
    process.waitForFinished();

    QByteArray output = process.readAllStandardOutput();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(output);
    QJsonObject jsonObj = jsonDoc.object();
    QJsonArray devices = jsonObj["blockdevices"].toArray();

    if (devices.isEmpty()) return;

    QJsonObject sda = devices.first().toObject();
    QTreeWidgetItem *parentItem = new QTreeWidgetItem(partitionTable);
    parentItem->setText(0, "/dev/sda");
    parentItem->setText(1, QString::number(sda["size"].toDouble() / (1024 * 1024)) + " MB");
    parentItem->setText(2, sda["type"].toString());
    parentItem->setText(3, "");
    partitionTable->addTopLevelItem(parentItem);

    if (sda.contains("children"))
    {
        QJsonArray partitions = sda["children"].toArray();
        for (const QJsonValue &partition : partitions)
        {
            QJsonObject partObj = partition.toObject();
            QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
            childItem->setText(0, "/dev/" + partObj["name"].toString());
            childItem->setText(1, QString::number(partObj["size"].toDouble() / (1024 * 1024)) + " MB");
            childItem->setText(2, partObj["type"].toString());
            childItem->setText(3, partObj["mountpoint"].toString().isEmpty() ? "Not Mounted" : partObj["mountpoint"].toString());
            parentItem->addChild(childItem);
        }
    }

    partitionTable->expandAll();
    partitionTable->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void DiskPartitions::addPartition()
{
    QMessageBox::information(this, "Add Partition", "Functionality to add a partition will be implemented here.");
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

void DiskPartitions::modifyPartition()
{
    QTreeWidgetItem *selectedItem = partitionTable->currentItem();
    if (!selectedItem || selectedItem->parent() == nullptr) return;

    QString partitionName = selectedItem->text(0);
    bool ok;
    QString newSize = QInputDialog::getText(this, "Modify Partition", "Enter new size for " + partitionName, QLineEdit::Normal, "", &ok);
    if (ok && !newSize.isEmpty()) {
        QMessageBox::information(this, "Modified", partitionName + " resized to " + newSize + " MB.");
    }
}
