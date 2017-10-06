#ifndef MIDIINPUT_H
#define MIDIINPUT_H

#include <QWidget>
#include <QDebug>

#ifdef Q_OS_MAC
#include <CoreMIDI/CoreMIDI.h>
#else
#include <Windows.h>
#include <MMSystem.h>
#include <Dbt.h>
#include "WindowsMidiTypes.h"
#endif

class MidiInput : public QWidget
{
    Q_OBJECT
public:
    explicit MidiInput(QWidget *parent = 0);

    bool enable;
    QString device;
    int channel;
    QString type;
    int number;
    QString instance;
    
signals:
    void signalSendInputToModlines(int val, QString instnace);
    
public slots:
    void slotReceiveInput(const MIDIPacket *packet, QString deviceName);
    
};

#endif // MIDIINPUT_H
