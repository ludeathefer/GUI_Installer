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
    double availableSpace;
private:
    void loadUi();
    void populatePartitions();
    void addPartition(double availableSpace);
    void deletePartition();
    void shrinkPartition();
    void unallocatePartition();
};

#endif // DISKDiskPartitions_H
