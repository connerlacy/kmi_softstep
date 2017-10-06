#ifndef LEDMANAGER_H
#define LEDMANAGER_H

#include <QObject>
#include <QDebug>
#include <QTimer>

#ifdef Q_OS_MAC
#include <CoreMIDI/CoreMIDI.h>
#else
#include <Windows.h>
#include <MMSystem.h>
#include <Dbt.h>
#include "WindowsMidiTypes.h"
#endif

class LEDManager : public QObject
{
    Q_OBJECT
public:
    explicit LEDManager(QObject *parent = 0);

    QTimer fifoClock;
    QList<MIDIPacket> packetFIFOList;
    QList<MIDIPacket> packetList;
    QList<MIDIPacket> lastPacketListSent;

    int keyInstanceNum;

    QString greenMode[6];
    QString redMode[6];

    void processLED(int modlineNum, int greenOrRed, QString mode);

    bool state[6];
    
signals:
    void signalSendLEDControl(QString port, QList<MIDIPacket> pktlst);
    
public slots:
    void slotReceiveModlineOutput(int modlineNum, int val);
    void slotSetLedModes(int modlineNum, QString gm, QString rm);
    void slotStateRecallLedLastPacket(QList<MIDIPacket> pktlst);

    void slotDrainFIFO();
    
};

#endif // LEDMANAGER_H
