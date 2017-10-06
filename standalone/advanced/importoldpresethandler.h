#ifndef IMPORTOLDPRESETHANDLER_H
#define IMPORTOLDPRESETHANDLER_H

#include <QObject>
#include <QVariant>
#include <QDebug>
#include <QtGui>
#include <QDesktopServices>
#include <QUrl>

#include "presetinterface.h"

class ImportOldPresetHandler : public QObject
{
    Q_OBJECT
public:
    explicit ImportOldPresetHandler(PresetInterface *pi, QObject *parent = 0);

    PresetInterface *presetInterface;

    //QJson::Parser   parser;

    //QFile *jsonFile;
    bool ok;

    QString presetName;
    QVariantMap importedOldPresetMap;
    QVariantMap importedNewPresetMap;

    QString mode;
    
signals:
    void signalPresetMenu(int numPresets);
    void signalAddRemovePreset();
    void signalImportingPresetNum(QString updatingMessage);
    void signalImportingComplete();
    void signalPathNotFound();
    void signalPathFound();
    
public slots:
    void slotImportOldPreset();
    QVariantMap slotConvertPreset();
    void slotNormalizePresetMap();
    QString slotListErrorCompensation(QList<QVariant> stringList);
    int slotEmptyListCompensation(QString oldName, QList<QVariant> valueList);
    QString slotGetNewTableValue(QString oldValue);
    QString slotGetOldDestinationParam(QString newParam, int keyNum, int modlineNum);
    void slotSetMode(QString m);
};

#endif // IMPORTOLDPRESETHANDLER_H
