#ifndef SYSEXCOMPOSER_H
#define SYSEXCOMPOSER_H

#include <QWidget>
#include <QVariant>
#include <QFile>
#include <QCoreApplication>

extern "C"
{
#include "softstep.h"
}

class SysExComposer : public QWidget
{
    Q_OBJECT
public:
    explicit SysExComposer(QWidget *parent = 0);
    //~SysExComposer();

    QVariantMap     defaultAttributeList;
    int             embeddedbuildNum, connectedBuildNum;
    QString         embeddedVersion, connectedVersion;
    unsigned char*  fwFile;
    int             fwFileSize;
    bool            isSoftStep2;

    //QList<QVariantMap> setlist;

    //t_softstep *x;

signals:
    void    signalSendSysEx(QString messageID, unsigned char* message, int messageLength, QString destinationName);
    void    signalSendBuildNums(int,QString, int, QString, int hardware);
    void    signalUpdateComplete();

public slots:
    void    slotComposeAttributeListFromSetlist(QList<QVariantMap> setlist, QVariantMap settingsMapGlobal, QList<int> pedalTable);
    void    slotGetConnectedVersion(QByteArray);
    void    slotGetEmbeddedVersion();
    void    slotUpdateFirmware();

    void    slotSettingsSent();
    void    slotPresetsSent();
};

#endif // SYSEXCOMPOSER_H
