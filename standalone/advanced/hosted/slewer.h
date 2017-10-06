#ifndef SLEWER_H
#define SLEWER_H

#include <QWidget>
#include <QTimer>
#include <QDebug>
#include "math.h"

class Slewer : public QWidget
{
    Q_OBJECT
public:
    explicit Slewer(QWidget *parent = 0);

    double          position;
    double          destination;
    double          velocity;
    QTimer*         timer;

    int lastOutput;
    
signals:
    void            signalOutput(int output);

public slots:
    void            slotSlew(double target, double time);
    void            slotUpdate();


};

#endif // SLEWER_H
