#ifndef MIDIPARSE_H
#define MIDIPARSE_H

#include <QWidget>

#include <QDebug>



#ifdef Q_OS_MAC
#include <CoreMIDI/CoreMIDI.h>
#include <CoreServices/CoreServices.h>
#include <CoreFoundation/CoreFoundation.h>
#else
#include <Windows.h>
#include <MMSystem.h>
#include <Dbt.h>
#include "WindowsMidiTypes.h"
#endif

class MidiParse : public QWidget
{
    Q_OBJECT
public:
    explicit MidiParse(QWidget *parent = 0);
    
signals:
    void signalUpdateSensor(int cc, int data);
    
public slots:
    void slotParsePacket(const MIDIPacket *packet);
    
};

#endif // MIDIPARSE_H
