#ifndef TRIGGER_H
#define TRIGGER_H

#include <QTimer>
#include <QThread>
#include <QDebug>

class Trigger : public QObject
{
    Q_OBJECT
    QThread triggerThread;
    QThread longTriggerThread;
    QThread fastTriggerThread;
    QThread dblTriggerThread;
    QThread offTriggerThread;
    QThread deltaTriggerThread;

    QThread longTriggerLatchThread;
    QThread fastTriggerLatchThread;
    QThread dblTriggerLatchThread;

public:
    Trigger();

    void trigger();

    void fastTrigger();

    void longTrigger();
    void longTriggerAbort();

    void dblTriggerHit();
    void dblTriggerAbort();
    bool dblWindowIsOpen;
    int  dblHitCount;

    void offTrigger();

    void deltaTrigger();

    //---------- Latch
    void fastTriggerLatch();

    void dblTriggerLatchHit();
    void dblTriggerLatchAbort();
    bool dblLatchWindowIsOpen;
    int  dblLatchHitCount;

    void longTriggerLatch();
    void longTriggerLatchAbort();

signals:
    //To DataCooker
    void signalTriggerReturn();
    void signalFastTriggerReturn();
    void signalLongTriggerReturn();
    void signalDblTriggerReturn();
    void signalOffTriggerReturn();

    //---- Latch
    void signalFastTriggerLatchReturn();
    void signalDblTriggerLatchReturn();
    void signalLongTriggerLatchReturn();

    //To Trigger Worker
    void signalStartTriggerClock(int timeout, QString type);
    void signalAbortClock(QString type);

public slots:
    void slotTriggerReturn();
    void slotFastTriggerReturn();
    void slotLongTriggerReturn();
    void slotDblTriggerReturn();
    void slotOffTriggerReturn();
    void slotDeltaTriggerReturn();

    //---- Latch
    void slotFastTriggerLatchReturn();
    void slotDblTriggerLatchReturn();
    void slotLongTriggerLatchReturn();
};

class TriggerWorker : public QObject
{
    Q_OBJECT

public:
    TriggerWorker(QString typ);
    ~TriggerWorker();

    QTimer* clock;
    QString triggerType;

signals:
    void signalSendTriggerTimeout();

public slots:
    void slotStartTriggerClock(int timeout, QString type);
    void slotAbortTriggerClock(QString type);
    void slotReturnTriggerTimeout();

};
#endif // TRIGGER_H
