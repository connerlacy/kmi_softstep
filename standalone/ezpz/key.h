#ifndef KEY_H
#define KEY_H

#include <QWidget>
#include <QtGui>
#include <QDebug>
#include <QVariant>

#ifdef Q_OS_MAC
#include "ui_keyform.h"
#else
#include "ui_keyformWin.h"
#endif


class Key : public QWidget
{
    Q_OBJECT
public:
    explicit Key(QWidget *parent = 0, int instanceNum = 0);

    int instance;
    QList<QCheckBox *> checkBoxes;

    QString source;
    QString table;

    bool isKeyOff();

    bool disableKeyEvent;
    void keyPressEvent(QKeyEvent *);


signals:
    void signalStoreValue(QString name, QVariant value, int presetNum);
    void signalCheckSavedState();
    
public slots:
    void slotConnectElements();
    void slotValueChanged();
    void slotRecallPreset(QVariantMap preset, QVariantMap master);

    void slotEnableDisableKeyEvents(bool);

private:
    Ui::keyForm keyForm;
};

#endif // KEY_H
