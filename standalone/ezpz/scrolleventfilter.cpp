#include "scrolleventfilter.h"

ScrollEventFilter::ScrollEventFilter(QObject *parent) :
    QObject(parent)
{
}

bool ScrollEventFilter::eventFilter(QObject *obj, QEvent *event)
{
    QWidget *widget = reinterpret_cast<QWidget *>(obj);

    if(!widget->underMouse() && event->type() == QEvent::Wheel)
    {
        return true;
    }
    else
    {
        //standard event processing
        return QObject::eventFilter(obj,event);
    }
}
