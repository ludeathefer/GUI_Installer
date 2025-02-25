#ifndef PAGE_H
#define PAGE_H

#include <QStackedWidget>

class Page : public QWidget
{
    Q_OBJECT
public:
    QStringList params;
    bool error;

    explicit Page(QStackedWidget *parent = nullptr);
    QFrame* createDivider();
    void setError(bool value);

signals:
    void errorChanged(bool changedValue);

public slots:
    //void onNextClick();
};

#endif // PAGE_H
