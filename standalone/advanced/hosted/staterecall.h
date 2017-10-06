#ifndef STATERECALL_H
#define STATERECALL_H

#include <QObject>
#include <QMap>
#include <QDebug>

#ifdef Q_OS_MAC
#include <CoreMIDI/CoreMIDI.h>
#else
#include <Windows.h>
#include <MMSystem.h>
#include <Dbt.h>
#include "WindowsMidiTypes.h"
#endif

class StateRecall : public QObject
{
    Q_OBJECT
public:
    explicit StateRecall(QObject *parent = 0);

    int                                 keyNum;
    bool                                initGate;
    bool                                parentIsNavPad;
    QString                             presetName;

    QList<MIDIPacket>                   getInitMIDIPacketList();

    QMap<QString, bool>                 toggleStates[6];
    QMap<QString, int>                  counterState;
    QMap<QString, int>                  yIncDecState;
    QMap<QString, int>                  xIncDecState;
    QMap<QString, bool>                 ledStates[6];
    QMap<QString, QList <MIDIPacket> >  lastMidiPacketList;
    QMap<QString, int>                  previousKeyValueState;
    QMap<QString, bool>                 initModeOnceCalledState[6];

signals:
    //Toggle -- received in modline.cpp
    void signalStateRecallToggles(int modlineNum, bool state);

    //Counter -- received in key.cpp
    void signalStateRecallCounter(int);

    //Inc-Dec -- received in datacooker.cpp
    void signalStateRecallYIncDec(int);
    void signalStateRecallXIncDec(int);

    //LEDs -- received in ledmanager.cpp
    void signalStateRecallLedStates(int modlineNum, bool state);
    void signalStateRecallLedLastPacketList(QList <MIDIPacket> pktlst);
    
public slots:
    //Init
    void slotInit(QList<QString> presetNames, int keyNumVal);
    void slotInitNewPreset(QString presetName);

    //Toggle
    void slotStoreToggleStates(int modlineNum, bool state);

    //Counter
    void slotStoreCounterState(int val);

    //Inc-Dec
    void slotStoreIncDecState(int x, int y);

    //LEDs
    void slotStoreLedStates(int modlineNum, bool state);
    void slotStoreLedLastPacketList(QList <MIDIPacket> pktlst);

    //Previous Key Value
    void slotStorePreviousKeyValueState(int val);

    //Init Mode
    void slotStoreInitModeState(int modlineNum, bool called);

    //-------- Recall
    void slotRecallState(QString name);
    
};

#endif // STATERECALL_H
