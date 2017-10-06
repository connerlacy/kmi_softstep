#include "delay.h"

Delay::Delay(QObject *parent) :
    QObject(parent)
{
}

void Delay::slotInputToDealy(int i)
{
    qDebug() << "delay input";
    buffer.append(i);
    QTimer::singleShot(delayTime, this, SLOT(slotSendOutput()));
}

void Delay::slotSendOutput()
{
    emit signalDelayedOutput(buffer.first());
    buffer.removeFirst();
}
