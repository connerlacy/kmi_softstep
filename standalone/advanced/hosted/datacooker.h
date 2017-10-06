#ifndef DATACOOKER_H
#define DATACOOKER_H

#include <QWidget>
#include <QMap>

#include "hosted/latcher.h"
#include "hosted/trigger.h"
#include "hosted/slewer.h"

#include "pedal.h"

class Key;
class MainWindow;

enum {NW, NE, SW, SE};
enum {N, E, W, S};

class DataCooker : public QWidget
{
    Q_OBJECT
public:
    explicit DataCooker(int instanceNum, QWidget *parent = 0);

    bool isSS2;

    enum {SINGLE_KEY, ADJACENT_KEYS, ALL_KEYS};

    Pedal *pedal;
    int pedalVal;

    Key *parentKey;
    MainWindow *mw;

    int                 sensorVals[4];
    int                 keyNum;
    QMap<int, int>      keySensorBaseCcMap;

    QMap<int, QString>  modlineSources;

    //Latching sources
    Latcher pressureLatcher;
    Latcher xLatcher;
    Latcher yLatcher;

    //Inc Dec
    QTimer* yIncClock;
    bool    yIncOrDec; //True means inc and False means dec, of course.
    QTimer* xIncClock;
    bool    xIncOrDec;
    int     yIncCount;
    int     xIncCount;
    int     yIncModlineNum;
    int     xIncModlineNum;
    int     lastYCount;
    int     lastXCount;

    //Triggers
    Trigger trigger;
    bool fastTrigState;
    bool dblTrigState;
    bool longTrigState;
    bool offTrigState;
    bool fastTrigLatchState;
    bool dblTrigLatchState;
    bool longTrigLatchState;

    int previousKeyPressed[2];

    void                cookLockout();
    void                cookRaw();
    void                cookSources();

    //------------------------------- Source Cooking
    int     pressureRaw();

    int     pressureLive();
    int     xLive();
    int     yLive();

    int    footOn();
    int    footOff();
    bool   footOnOff;

    int    modlineOutput(int modlineNum);

    int     pressureLatch(int modlineNum);
    int     xLatch(int modlineNum);
    int     yLatch(int modlineNum);

    void     xIncrement();
    void     yIncrement();

    int top();
    int bottom();

    void    fastTrig();
    void    dblTrig();
    void    longTrig();
    void    offTrig();
    void    deltaTrig();

    void    fastTrigLatch();
    void    dblTrigLatch();
    void    longTrigLatch();

    //------------------------ Settings
    int onThresh;
    int offThresh;
    int yDeadZone;
    int xDeadZone;
    int yAccel;
    int xAccel;

    int sensorResponse; //0 - maximum 1 - avg
    float globalGain;

    //Key Safety
    int keySafetyMode;
    bool activateKey;
    QList<int> lockoutKeysPressed; //Pre Cooking
    QList<int> adjacentKeyLockoutList[10];

    //Probably don't need both of these, but just to be sure initially
    int navYCount;
    int navYDecade;

    
signals:
    void signalTransformSource(int data, int modlineNum, QString source);
    void signalThisKeyPressed(int keyPressed);
    void signalThisKeyOff(int keyOff);

    //Key Safetey / Lockout signals
    void signalLockoutKeyPressedReleased(int keyNumber,bool pressedReleased);

    //increment sources clock start/stop
    void signalXIncClockStart(int num);
    void signalXIncClockStop();
    void signalYIncClockStart(int num);
    void signalYIncClockStop();

    
public slots:
    void slotUpdateVals(int cc, int val);
    void slotReceiveModlineOutput(int modlineNum, int val);

    void slotSetSource(QString source, int modlineInstance);

    //----------------------------- Latching Return Slots
    void slotPressureLatchReturn(int val, int modlineNum);
    void slotXLatchReturn(int val, int modlineNum);
    void slotYLatchReturn(int val, int modlineNum);

    //----------------------------- IncDec Clock Slots
    void slotTickXIncrementClock();
    void slotTickYIncrementClock();
    void slotYIncSet(int);
    void slotXIncSet(int);

    //----------------------------- Trigger Return and Off Slots
    //Fast
    void slotFastTriggerReturn();
    void slotFastTriggerOff();

    //Long
    void slotLongTriggerReturn();
    void slotLongTriggerOff();

    //Dbl
    void slotDblTriggerReturn();
    void slotDblTriggerOff();

    //Off
    void slotOffTriggerReturn();
    void slotOffTriggerOff();

    //--------- Trigger Latch
    //Fast
    void slotFastTriggerLatchReturn();
    void slotFastTriggerLatchOff();

    //Long
    void slotLongTriggerLatchReturn();
    void slotLongTriggerLatchOff();

    //Dbl
    void slotDblTriggerLatchReturn();
    void slotDblTriggerLatchOff();

    //------------------------------------------------------ Keys
    void slotReceiveKeyPressed(int keyPressed);

    //----------------------------- Key # Pressed
    void slotKeyPressed();

    //------------------------------------------------------ Midi Input
    void slotReceiveMidiInput(int val, QString instance);

    void slotReceiveNavY(int count);
    void slotReceiveNavDecade(int decade);

    //------------------------------------------------------ State Recall
    void slotStateRecallYIncDec(int);
    void slotStateRecallXIncDec(int);

    //------------------------------------------------------ Settings
    void slotSetOnThresh(int key, int threshold);
    void slotSetOffThresh(int key, int threshold);
    void slotSetYDeadZone(int key, int deadZone);
    void slotSetXDeadZone(int key, int deadZone);
    void slotSetYAccel(int key, int accel);
    void slotSetXAccel(int key, int accel);

    void slotSetGlobalGain(float val);
    void slotSetSensorResponse(int response);
    void slotSetKeySafetyMode(int mode);

    //------------------------------------------------------- Key Safety / Lockout
    void slotSetParentKey(Key *pK);
    void slotLockoutKeyPressedReleased(int keyNumber, bool pressedReleased);

    //------------------------------------------------------- OSC
    void slotReceiveOscInput(int inputNum, int val);

    //increment sources clock start/stop
    void slotXIncClockStart(int num);
    void slotXIncClockStop();
    void slotYIncClockStart(int num);
    void slotYIncClockStop();

};

#endif // DATACOOKER_H
