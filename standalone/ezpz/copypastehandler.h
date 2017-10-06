#ifndef COPYPASTEHANDLER_H
#define COPYPASTEHANDLER_H

#include <QObject>
#include <QVariant>
#include <QtGui>
#include <QDesktopServices>
#include <QUrl>
#include "presetinterface.h"
#include "mididevicemanager.h"

class CopyPasteHandler : public QObject
{
    Q_OBJECT
public:
    explicit CopyPasteHandler(PresetInterface *presetInterfacer, QObject *parent = 0);

    PresetInterface *presetInterface;

    QVariantMap presetCopiedMap;
    
signals:
    void signalUpdatePasteAvailability();
    
public slots:
    void slotCopyPreset();
    void slotPastePreset();
};

#endif // COPYPASTEHANDLER_H
