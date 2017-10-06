#include "latcher.h"

Latcher::Latcher()
{
    //start timer
    currentTime = 0;
    delayTime = 1000;
    //start(1);
    //connect(this, SIGNAL(timeout()), this, SLOT(slotDrainFIFO()));

    //Create a latcher worker and move it to a new thread
    LatcherWorker* latcherWorker = new LatcherWorker;
    latcherWorker->moveToThread(&workerThread);

    latchOpen = false;

    connect(this, SIGNAL(signalProcessInput(int)), latcherWorker, SLOT(slotProcessInput(int)));
    connect(&latcherWorker->slewer, SIGNAL(signalOutput(int)), latcherWorker, SLOT(slotReturnInput(int)));
    connect(latcherWorker, SIGNAL(signalSendLatchedValue(int)), this, SLOT(slotReceiveLatchedValue(int)));

    workerThread.start();

}

Latcher::~Latcher()
{
    workerThread.quit();
    workerThread.wait();
}

void Latcher::receiveInput(int val, int modlineNum)
{
    if(latchOpen)
    {
        currentModline = modlineNum;
        //qDebug() << "input from source stream" << input;

        emit signalProcessInput(val);
    }
}

void Latcher::slotInputFromStream(const int &val)
{
    //qDebug() << "latch buffer" << buffer.first();
    //buffer.removeFirst();
}

void Latcher::slotReceiveLatchedValue(const int &val)
{
    if(latchOpen)
    {
        emit signalReturnValue(val, currentModline);
    }
    else
    {
        buffer.clear();
    }

}

int Latcher::latchInput()
{
   return -1;
}

//----------------- Latcher Worker
LatcherWorker::LatcherWorker()
{

}

LatcherWorker::~LatcherWorker()
{

}

void LatcherWorker::slotProcessInput(const int &val)
{
    input.append(val);
    QTimer::singleShot(100, this, SLOT(slotDelayInput()));
}

void LatcherWorker::slotDelayInput()
{
    emit signalSendLatchedValue(input.first());
    //slewer.slotSlew(input.first(), 1);
    input.removeFirst();
    //qDebug() << "dealyed output" << input;
}

void LatcherWorker::slotReturnInput(int val)
{
    lastVal = -1;

    if(lastVal != val)
    {
        emit signalSendLatchedValue(val);
        lastVal = val;
    }

}

