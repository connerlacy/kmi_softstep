#ifndef ALPHANUMMANAGER_H
#define ALPHANUMMANAGER_H

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

class AlphaNumManager : public QObject
{
    Q_OBJECT
public:
    explicit AlphaNumManager(QObject *parent = 0);

    QTimer fifoClock;
    QList<MIDIPacket> packetFIFOList;
    QList<MIDIPacket> packetList;

    int instanceNum;
    QString displayMode;
    QString keyName;
    QString prefix;
    QString postfix; //Only used with nav pad in program change mode

    QString currentPresetName;

    bool paramDisplay;

    bool keyOnOff;

    QTimer keyOffTimeout;
    
signals:
    void signalSendDisplayVals(QString port, QList<MIDIPacket> packet);
    
public slots:
    void slotDisplayKeyName(int keyNum);
    void slotDisplayParam(int modlineNum, int val);
    void slotPresetChangeDisplayPresetName();
    void slotFormatAndOutputString(QString displayString);
    void slotReturnToKeyName();
    void slotKeyOff(int keyNum);
    void slotKeyOffTimeout();

    //---------------------- Gates
    void slotOpenParamDisplay();
    void slotCloseParamDisplay();

    void slotDrainFIFO();


    
};

#endif // ALPHANUMMANAGER_H
