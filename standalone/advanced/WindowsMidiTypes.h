#ifndef WINODWSMIDITYPES_H
#define WINODWSMIDITYPES_H

#ifdef Q_OS_MAC

#else

#include <Windows.h>

typedef struct
{
    int timestamp;
    int length;

    union
    {
        DWORD dwData;
        BYTE bData[4];
    };

    unsigned char data[256];
    int timeStamp;

} MIDIPacket;

typedef int MIDIEndpointRef;

#endif //Q_OS_MAC

#endif // WINODWSMIDITYPES_H
