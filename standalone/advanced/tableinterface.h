#ifndef TABLEINTERFACE_H
#define TABLEINTERFACE_H

#include <QWidget>
#include <QtGui>
#include <QLayout>
#include <QtQml/QQmlEngine>
#include <QtQuick/QQuickView>
#include <QDebug>

#ifdef Q_OS_MAC
#include "ui_pedalLiveTableForm.h"
#else
#include "ui_pedalLiveTableFormWin.h"
#endif

class TableInerface : public QWidget
{
    Q_OBJECT
public:
    explicit TableInerface(QWidget *parent = 0);
    QObject* rootObject;

    QWidget *qmlWidget;

    QMap<QString, unsigned char *> tableMap;
    QList<QObject *> blocks;

signals:

public slots:
    void slotDrawTable(float x, float y, float width);
    void slotClearTable();
    void slotDrawLinear();


private:
    Ui::PedalLiveTableForm pedalLiveTableForm;
    
};

#endif // TABLEINERFACE_H
