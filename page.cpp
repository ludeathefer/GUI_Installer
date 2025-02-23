#include "page.h"

Page::Page(QStackedWidget *parent)
    : QWidget{parent}
{

}

QFrame* Page::createDivider()
{
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    return line;
}
