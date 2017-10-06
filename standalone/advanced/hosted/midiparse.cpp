#include "midiparse.h"

MidiParse::MidiParse(QWidget *parent) :
    QWidget(parent)
{
}

//Used only for SSCOM Port 1 data, tethered data
void MidiParse::slotParsePacket(const MIDIPacket* packet)
{
    if(packet->data[0] == 176)
    {
        //qDebug() << "midi parse call" << packet->data[1] << packet->data[2];
        emit signalUpdateSensor(packet->data[1], packet->data[2]);
    }
}
