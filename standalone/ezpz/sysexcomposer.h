#ifndef SYSEXCOMPOSER_H
#define SYSEXCOMPOSER_H

#include <QWidget>
#include <QVariant>
#include <QFile>
#include <QCoreApplication>

#include "factorypresets.h"

extern "C"
{
#include "softstep.h"
}

class SysExComposer : public QWidget
{
    Q_OBJECT
public:
    explicit SysExComposer(QWidget *parent = 0);
    ~SysExComposer();

    QVariantMap     defaultAttributeList;
    int             embeddedbuildNum, connectedBuildNum;
    QString         embeddedVersion, connectedVersion;
    unsigned char*  fwFile;
    int             fwFileSize;
    bool            isSoftStep2;

    FactoryPresets* factoryPresets;
    bool            isFactoryPreset[10];
    
signals:
    void    signalSendSysEx(QString messageID, unsigned char* message, int messageLength, QString destinationName);
    void    signalSendBuildNums(int,QString, int, QString);
    void    signalUpdateComplete();
    
public slots:
    void    slotComposeAttributeListFromPreset(QVariantMap presetSent, QVariantMap, qlonglong);
    void    slotGetConnectedVersion(QByteArray);
    void    slotGetEmbeddedVersion();
    void    slotUpdateFirmware();
    void    slotComposeFactoryPreset(long p, QString factoryPresetName, t_softstep *x);

    void    slotSettingsSent();
    void    slotPresetsSent();
};

#endif // SYSEXCOMPOSER_H
