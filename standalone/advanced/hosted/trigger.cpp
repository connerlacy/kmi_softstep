#include "trigger.h"

#define TRIGGER_TIMEOUT 500
#define FAST_TRIG_TIMEOUT 0
#define OFF_TRIG_TIMEOUT 0
#define LONG_TRIG_TIMEOUT 1000
#define DBL_TRIG_WINDOW 600
#define LATCH_TRIG_TIMEOUT 30

Trigger::Trigger()
{

    TriggerWorker* triggerWorker = new TriggerWorker("trig");
    TriggerWorker* fastTriggerWorker = new TriggerWorker("fastTrig");
    TriggerWorker* longTriggerWorker = new TriggerWorker("longTrig");
    TriggerWorker* dblTriggerWorker = new TriggerWorker("dblTrig");
    TriggerWorker* offTriggerWorker = new TriggerWorker("offTrig");

    TriggerWorker* fastTriggerLatchWorker = new TriggerWorker("fastTrigLatch");
    TriggerWorker* longTriggerLatchWorker = new TriggerWorker("longTrigLatch");
    TriggerWorker* dblTriggerLatchWorker = new TriggerWorker("dblTrigLatch");

    //Regular
    triggerWorker->moveToThread(&triggerThread);
    connect(this, SIGNAL(signalStartTriggerClock(int,QString)), triggerWorker, SLOT(slotStartTriggerClock(int,QString)));
    connect(triggerWorker, SIGNAL(signalSendTriggerTimeout()), this, SLOT(slotTriggerReturn()));
    connect(this, SIGNAL(signalAbortClock(QString)), triggerWorker, SLOT(slotAbortTriggerClock(QString)));

    //Fast
    fastTriggerWorker->moveToThread(&fastTriggerThread);
    connect(this, SIGNAL(signalStartTriggerClock(int,QString)), fastTriggerWorker, SLOT(slotStartTriggerClock(int,QString)));
    connect(fastTriggerWorker, SIGNAL(signalSendTriggerTimeout()), this, SLOT(slotFastTriggerReturn()));
    connect(this, SIGNAL(signalAbortClock(QString)), fastTriggerWorker, SLOT(slotAbortTriggerClock(QString)));

    //Long
    longTriggerWorker->moveToThread(&longTriggerThread);
    connect(this, SIGNAL(signalStartTriggerClock(int,QString)), longTriggerWorker, SLOT(slotStartTriggerClock(int,QString)));
    connect(longTriggerWorker, SIGNAL(signalSendTriggerTimeout()), this, SLOT(slotLongTriggerReturn()));
    connect(this, SIGNAL(signalAbortClock(QString)), longTriggerWorker, SLOT(slotAbortTriggerClock(QString)));

    //Dbl
    dblWindowIsOpen = false;
    dblHitCount = 0;
    dblTriggerWorker->moveToThread(&dblTriggerThread);
    connect(this, SIGNAL(signalStartTriggerClock(int,QString)), dblTriggerWorker, SLOT(slotStartTriggerClock(int,QString)));
    connect(dblTriggerWorker, SIGNAL(signalSendTriggerTimeout()), this, SLOT(slotDblTriggerReturn()));
    connect(this, SIGNAL(signalAbortClock(QString)), dblTriggerWorker, SLOT(slotAbortTriggerClock(QString)));

    //Off
    offTriggerWorker->moveToThread(&offTriggerThread);
    connect(this, SIGNAL(signalStartTriggerClock(int,QString)), offTriggerWorker, SLOT(slotStartTriggerClock(int,QString)));
    connect(offTriggerWorker, SIGNAL(signalSendTriggerTimeout()), this, SLOT(slotOffTriggerReturn()));
    connect(this, SIGNAL(signalAbortClock(QString)), offTriggerWorker, SLOT(slotAbortTriggerClock(QString)));

    //----- Latch
    //Fast
    fastTriggerLatchWorker->moveToThread(&fastTriggerLatchThread);
    connect(this, SIGNAL(signalStartTriggerClock(int,QString)), fastTriggerLatchWorker, SLOT(slotStartTriggerClock(int,QString)));
    connect(fastTriggerLatchWorker, SIGNAL(signalSendTriggerTimeout()), this, SLOT(slotFastTriggerLatchReturn()));
    connect(this, SIGNAL(signalAbortClock(QString)), fastTriggerLatchWorker, SLOT(slotAbortTriggerClock(QString)));

    //Long
    longTriggerLatchWorker->moveToThread(&longTriggerLatchThread);
    connect(this, SIGNAL(signalStartTriggerClock(int,QString)), longTriggerLatchWorker, SLOT(slotStartTriggerClock(int,QString)));
    connect(longTriggerLatchWorker, SIGNAL(signalSendTriggerTimeout()), this, SLOT(slotLongTriggerLatchReturn()));
    connect(this, SIGNAL(signalAbortClock(QString)), longTriggerLatchWorker, SLOT(slotAbortTriggerClock(QString)));

    //Dbl
    dblLatchWindowIsOpen = false;
    dblLatchHitCount = 0;
    dblTriggerLatchWorker->moveToThread(&dblTriggerLatchThread);
    connect(this, SIGNAL(signalStartTriggerClock(int,QString)), dblTriggerLatchWorker, SLOT(slotStartTriggerClock(int,QString)));
    connect(dblTriggerLatchWorker, SIGNAL(signalSendTriggerTimeout()), this, SLOT(slotDblTriggerLatchReturn()));
    connect(this, SIGNAL(signalAbortClock(QString)), dblTriggerLatchWorker, SLOT(slotAbortTriggerClock(QString)));
}

//---------------------------------------- Trigger
void Trigger::trigger()
{
    //No delay on trigger, but still need extra thread for delayed trigger-off message
    triggerThread.start();
    emit signalStartTriggerClock(TRIGGER_TIMEOUT, "trig");
}

void Trigger::slotTriggerReturn()
{
    triggerThread.quit();
    emit signalTriggerReturn();
}

//---------------------------------------- Long
void Trigger::longTrigger()
{
    longTriggerThread.start();
    emit signalStartTriggerClock(LONG_TRIG_TIMEOUT, "longTrig");
}

void Trigger::longTriggerAbort()
{
    emit signalAbortClock("longTrig");
    longTriggerThread.quit();
}

void Trigger::slotLongTriggerReturn()
{
    longTriggerThread.quit();
    emit signalLongTriggerReturn();
}

//---------------------------------------- Long Latch
void Trigger::longTriggerLatch()
{
    longTriggerLatchThread.start();
    emit signalStartTriggerClock(LONG_TRIG_TIMEOUT, "longTrigLatch");
}

void Trigger::longTriggerLatchAbort()
{
    emit signalAbortClock("longTrigLatch");
    longTriggerLatchThread.quit();
}

void Trigger::slotLongTriggerLatchReturn()
{
    longTriggerLatchThread.quit();
    emit signalLongTriggerLatchReturn();
}

//---------------------------------------- Fast
void Trigger::fastTrigger()
{
    //No delay on trigger, but still need extra thread for delayed trigger-off message
    fastTriggerThread.start();
    emit signalStartTriggerClock(FAST_TRIG_TIMEOUT, "fastTrig");
}

void Trigger::slotFastTriggerReturn()
{
    fastTriggerThread.quit();
    emit signalFastTriggerReturn();
}


//---------------------------------------- Fast Latch
void Trigger::fastTriggerLatch()
{
    fastTriggerLatchThread.start();
    emit signalStartTriggerClock(FAST_TRIG_TIMEOUT, "fastTrigLatch");
}

void Trigger::slotFastTriggerLatchReturn()
{
    fastTriggerLatchThread.quit();
    emit signalFastTriggerLatchReturn();
}

//---------------------------------------- Dbl
void Trigger::dblTriggerHit()
{
    if(!dblWindowIsOpen)
    {
        dblHitCount = 1;
        dblWindowIsOpen = true;
        dblTriggerThread.start();
        emit signalStartTriggerClock(DBL_TRIG_WINDOW, "dblTrig");
    }
    else
    {
        dblHitCount = 0;
        dblWindowIsOpen = false;
        emit signalAbortClock("dblTrig");
        emit signalDblTriggerReturn();
        dblTriggerThread.quit();
    }
}

void Trigger::dblTriggerAbort()
{
    emit signalAbortClock("dblTrig");
}

void Trigger::slotDblTriggerReturn()
{
    dblTriggerThread.quit();
    dblHitCount = 0;
    dblWindowIsOpen = false;
}

//---------------------------------------- Dbl Latch
void Trigger::dblTriggerLatchHit()
{

    if(!dblLatchWindowIsOpen)
    {
        dblLatchHitCount = 1;
        dblLatchWindowIsOpen = true;
        dblTriggerLatchThread.start();
        emit signalStartTriggerClock(DBL_TRIG_WINDOW, "dblTrigLatch");
    }
    else
    {
        dblLatchHitCount = 0;
        dblLatchWindowIsOpen = false;
        emit signalAbortClock("dblTrigLatch");
        emit signalDblTriggerLatchReturn();
        dblTriggerLatchThread.quit();
    }
}

void Trigger::dblTriggerLatchAbort()
{
    emit signalAbortClock("dblTrigLatch");
}

void Trigger::slotDblTriggerLatchReturn()
{
    dblTriggerLatchThread.quit();
    dblLatchHitCount = 0;
    dblLatchWindowIsOpen = false;
}

//---------------------------------------- Off
void Trigger::offTrigger()
{
    //No delay on trigger, but still need extra thread for delayed trigger-off message
    offTriggerThread.start();
    emit signalStartTriggerClock(OFF_TRIG_TIMEOUT, "offTrig");
}

void Trigger::slotOffTriggerReturn()
{
    qDebug() << "off trigger";
    offTriggerThread.quit();
    emit signalOffTriggerReturn();
}


//---------------------------------------- Delta
void Trigger::deltaTrigger()
{

}

void Trigger::slotDeltaTriggerReturn()
{

}


//--------------------- Trigger Worker

TriggerWorker::TriggerWorker(QString typ)
{
    triggerType = typ;
}

TriggerWorker::~TriggerWorker()
{

}

void TriggerWorker::slotStartTriggerClock(int timeout, QString type)
{
    if(triggerType == type)
    {
        qDebug() << "start trigger clock";

        clock = new QTimer(this);
        connect(clock, SIGNAL(timeout()), this, SLOT(slotReturnTriggerTimeout()));
        clock->setSingleShot(true);
        clock->start(timeout);
    }
}

void TriggerWorker::slotAbortTriggerClock(QString type)
{
    if(triggerType == type)
    {
       clock->stop();
    }
}

void TriggerWorker::slotReturnTriggerTimeout()
{
    qDebug() << "trigger timed out";
    emit signalSendTriggerTimeout();
}
