#ifndef DISKDiskPartitions_H
#define DISKDiskPartitions_H

#include "page.h"
#include <QTreeWidget>

class DiskPartitions : public Page
{
    Q_OBJECT
public:
    QTreeWidget* partitionTable;
    DiskPartitions(QStackedWidget *parent = nullptr);
private:
    void loadUi();
    void populatePartitions();
    void addPartition();
    void deletePartition();
};

#endif // DISKDiskPartitions_H
