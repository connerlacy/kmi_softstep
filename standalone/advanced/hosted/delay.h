#ifndef DELAY_H
#define DELAY_H

#include <QObject>
#include <QTimer>
#include <QDebug>

class Delay : public QObject
{
    Q_OBJECT
public:
    explicit Delay(QObject *parent = 0);

    int delayTime;
    QList<int> buffer;
    
signals:
    void signalDelayedOutput(int);

public slots:
    void slotInputToDealy(int i);
    void slotSendOutput();
    
};

#endif // DELAY_H
