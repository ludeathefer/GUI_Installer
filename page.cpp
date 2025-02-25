#include "page.h"

Page::Page(QStackedWidget *parent)
    : QWidget{parent}
{
    error = false;
}

QFrame* Page::createDivider()
{
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    return line;
}

void Page::setError(bool value)
{
    if (error == value) return;
    error = value;
    emit errorChanged(value);
}
