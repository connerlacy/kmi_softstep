#ifndef DISPLAYSINK_H
#define DISPLAYSINK_H

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

class DisplaySink : public QObject
{
    Q_OBJECT
public:
    explicit DisplaySink(QObject *parent = 0);

    QList<MIDIPacket> ledLastPacketList; //Most recent led message group, for filtering changes

    QTimer alphaFIFOClock; //Clock for polling most recent display message
    QList<MIDIPacket> mostRecentAlphaList; //Most recent display message group
    QList<MIDIPacket> alphaLastPacketList; //last alpah message received, for change filtering


    QList<MIDIPacket> displayFIFO; //queue of display messages (led, alphanumerics)
    QTimer displayFIFOClock; //Clock for draining display messages
    
signals:
    void signalSendPacket(QString port, MIDIPacket packet);
    
public slots:
    void slotAddLEDPacket(QString port, QList<MIDIPacket> packetList);
    void slotAddAlphaPacket(QString port, QList<MIDIPacket> packetList);

    void slotPollAlphaList();

    void slotDrainDisplayFIFO();
};

#endif // DISPLAYSINK_H
