#ifndef PRESETINTERFACE_H
#define PRESETINTERFACE_H

#include <QWidget>
#include <QDebug>
#include <QVariant>
#include <QtGui>
#include <QFileDialog>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QAction>
#include <QCheckBox>

#include "qjson/src/parser.h"
#include "qjson/src/serializer.h"

#define NUM_PRESETS 10

class PresetInterface : public QWidget
{
    Q_OBJECT
public:
    explicit PresetInterface(QWidget *parent = 0);

    QVariantMap jsonMasterMap;
    QVariantMap jsonMasterMapCopy;
    QVariantMap defaultParamMap;

    QSettings *settings;

    QJson::Parser       parser;
    QJson::Serializer   serializer;

    QFile *jsonFile;
    bool ok;

    QString jsonPath;

    int     currentPresetNum;
    QVariantMap currentPresetMap;
    bool connected; //is softstep connected? used to prevent download if not connected.
    void closeEvent(QCloseEvent *);

    void writeDefualtJSON();
    
signals:
    void signalRecallPreset(QVariantMap,QVariantMap);
    void signalAttributeFormatPreset(QVariantMap, QVariantMap, qlonglong);
    void signalUpdateStarted();
    void signalPresetDirty(bool);

    void signalSetPresetToFactory(int, QString);
    
public slots:
    void slotStoreValue(QString name, QVariant value, int presetNum);
    void slotCheckSaveState();
    void slotStoreGlobal();

    void slotReadJSON();
    void slotWriteJSON(QVariantMap jsonMap);

    void slotConstructDefaultMap();
    void slotRecallPreset(int i);
    void slotRevertPreset();

    void slotImportPreset();
    void slotExportPreset();

    void slotUpdateClicked();

    void slotSetCurrentPresetToFactory();
    
};

#endif // PRESETINTERFACE_H
