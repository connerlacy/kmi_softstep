#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVariant>
#include <QDebug>
#include <QVariant>

#include "key.h"
#include "navkey.h"
#include "settings.h"
#include "setlist.h"
#include "presetinterface.h"
#include "mididevicemanager.h"
#include "sysexcomposer.h"
#include "copypastehandler.h"
#include "scrolleventfilter.h"
#include "importoldpresethandler.h"

#ifdef Q_OS_MAC
#include "ui_fwoodform.h"
#include "ui_fwprogressform.h"
#include "ui_fwupdatecompleteform.h"
#include "ui_updatefwform.h"
#include "ui_aboutform.h"
#include "ui_mainwindow.h"
#include "ui_saveAsForm.h"
#include "ui_deletePresetForm.h"
#include "ui_importOldPresetsForm.h"
#include "ui_importOldNotFoundForm.h"
#include "ui_modlineWarningForm.h"
#else
#include "ui_fwoodformWin.h"
#include "ui_fwprogressformWin.h"
#include "ui_fwupdatecompleteformWin.h"
#include "ui_updatefwformWin.h"
#include "ui_aboutformWin.h"
#include "ui_mainwindowWin.h"
#include "ui_saveAsFormWin.h"
#include "ui_deletePresetFormWin.h"
#include "ui_importOldPresetsFormWin.h"
#include "ui_importOldNotFoundFormWin.h"
#include "ui_modlineWarningFormWin.h"
#endif

#include "hosted/midiparse.h"
#include "hosted/displaysink.h"
#include "hosted/oscinterface.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QSettings *sessionSettings;

    SysExComposer* sysExComposer;
    PresetInterface* presetInterface;
    MidiDeviceManager* midiDeviceManager;
    CopyPasteHandler* copyPasteHandler;
    MidiParse* midiParse;
    DisplaySink displaySink;
    ScrollEventFilter scrollEventFilter;
    ImportOldPresetHandler* importOldPresetHandler;
    OscInterface *oscInterface;

    //--------------------------------- Mode Switching
    QString mode;

    QStringList standaloneDestinations;
    QStringList standaloneSources;
    QStringList standaloneTables;
    QStringList hostedDestinations;
    QStringList hostedSources;
    QStringList hostedTables;
    QStringList standaloneNavSources;
    QStringList standaloneNavTables;
    QStringList hostedNavSources;
    QStringList hostedNavTables;
    QStringList hostedDisplayModes;
    QStringList standaloneDisplayModes;

    //Disabling Widget
    QWidget     *disableWidget;

    //Dialogs
    QWidget     *saveAsDialogWidget;
    QWidget     *deleteDialogWidget;
    QWidget     *fwoodDialogWidget;
    QWidget     *fwProgressDialogWidget;
    QWidget     *fwUpdateCompleteDialogWidget;
    QWidget     *fwUpdateDialogWidget;
    QWidget     *aboutFormWidget;
    QWidget     *importOldDialogWidget;
    QWidget     *importOldNotFoundDialogWidget;
    QWidget     *modlineWarningDialogWidget;

    //Menubar
    QMenuBar *menubar;
    QList<QAction *> actionList;

    QAction* updatefw;

    //copy / paste actions
    QAction* clearPresetAct;
    QAction* copyPresetAct;
    QAction* pastePresetAct;
    QAction* pasteNewPresetAct;
    QAction* copyKeyAct;
    QAction* pasteKeyAct;
    QAction* toolTipsEnable;
    QAction* importOldPreset;

    //Ui Elements
    Key *key[10];
    NavKey *navKey;
    Settings *settingsWindow;
    Setlist *setlist;

    QString connectedVersionString;
    int connectedVersionInt;

    //Key Lockout
    QList<int> lockoutKeysPressed;

    void closeEvent(QCloseEvent *);

#ifdef Q_OS_MAC
#else
    QProcess *syxutilProcess;
#endif

signals:
    void signalSaveAs(QString presetName);
    void signalSetMode(QString mode);
    void signalStoreValue(QString name, QVariant value, int presetNum);
    void signalCheckSavedState();
    void signalSelectedKeyOutline(int selectedKey, bool outlined);

    void signalSetPresetNameInKeys(QString);

public slots:
    void slotConnectInterfaces();
    void slotConnectElements();
    void slotDisconnectElements();

    //------------- Menu Bar
    void slotInitMenuBar();
    void slotOpenDoc();
    void slotEnableDisableToolTips();

    void slotUpdatePasteAvailability();
    void slotSelectedKey(int selectedKey);

    void slotValueChanged();
    void slotRecallPreset(QVariantMap, QVariantMap);

    void slotConnected(bool);

    void slotSaveAs();
    void slotPopulatePresetMenu();
    void slotSetPresetMenu(int presetNum);
    void slotDisplaySaveState(bool);

    void slotModlineWarning(QString modlineWarningMessage);

    void slotSetMode();
    void slotPopulateSourceDestLists();
    void slotPopulateDeviceMenus(QMap<QString, MIDIEndpointRef> externalDevices);

    void slotReceiveVersions(int connected, QString connectedVersion, int embedded, QString embeddedVersion, int hardware);

    void slotRecallPresetFromSetlist(QString presetName);

    //-------------- Firmware Updating
    void slotUpdateFirmware();
    void slotUpdateFwProgressBar(int);

    //-------------- Lockout Handling
    void slotLockoutKeyPressedReleased(int keyNumber, bool pressedReleased);

    //-------------- Standalone Preset Updating / Sending
    void slotUpdatePresets();
    void slotDisconnectUpdate();
    void slotConnectUpdate();

private:
    Ui::MainWindow *ui;

    //Dialogs
    Ui::saveAsDialogForm        *saveAsDialogForm;
    Ui::deleteDialogForm        *deleteDialogForm;

    Ui::FwoodDialog             *fwoodDialogForm;
    Ui::FwProgressForm          *fwProgressDialog;
    Ui::FwUpdateCompleteForm    *fwUpdateCompleteDialog;
    Ui::UpdateFirmwareForm      *fwUpdateDialog;
    Ui::AboutForm               *aboutForm;
    Ui::ImportOldPresetsForm    *importOldDialog;
    Ui::ImportOldNotFoundForm   *importOldNotFoundDialog;
    Ui::ModlineWarningForm      *modlineWarningDialog;



};

#endif // MAINWINDOW_H
