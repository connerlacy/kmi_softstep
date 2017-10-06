#ifndef LATCHER_H
#define LATCHER_H

#include <QTimer>
#include <QThread>
#include <QDebug>

#include "hosted/slewer.h"

class Latcher : public QTimer
{
    Q_OBJECT
    QThread workerThread;

public:

    Latcher();
    ~Latcher();

    QList<int> buffer;
    int currentModline;
    bool latchOpen;

    int currentTime;
    int delayTime;

    void receiveInput(int val, int modlineNum);
    int latchInput();

signals:
    void signalProcessInput(const int &val);
    void signalReturnValue(int val, int modlineNum);


public slots:
    void slotInputFromStream(const int &val);
    void slotReceiveLatchedValue(const int &val);
};

class LatcherWorker : public QObject
{
    Q_OBJECT



public:
    LatcherWorker();
    ~LatcherWorker();

        int lastVal;

    Slewer slewer;
    QList<int> input;

signals:
    void signalSendLatchedValue(const int &val);

public slots:
    void slotProcessInput(const int &val);
    void slotDelayInput();
    void slotReturnInput(int val);

};

#endif // LATCHER_H
