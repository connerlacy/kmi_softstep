#ifndef SCROLLEVENTFILTER_H
#define SCROLLEVENTFILTER_H

#include <QObject>
#include <QDebug>
#include <QEvent>
#include <QWidget>

class ScrollEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit ScrollEventFilter(QObject *parent = 0);
    bool toolTipsOn;

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    
signals:
    
public slots:
    
};

#endif // SCROLLEVENTFILTER_H
