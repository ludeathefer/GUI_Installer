#ifndef PAGE_H
#define PAGE_H

#include <QStackedWidget>

class Page : public QWidget
{
    Q_OBJECT
public:
    QStringList params;

    explicit Page(QStackedWidget *parent = nullptr);
    QFrame* createDivider();

signals:
};

#endif // PAGE_H
