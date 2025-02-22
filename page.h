#ifndef PAGE_H
#define PAGE_H

#include <QStackedWidget>

class Page : public QWidget
{
    Q_OBJECT
public:
    explicit Page(QStackedWidget *parent = nullptr);

    QStringList params;
signals:
};

#endif // PAGE_H
