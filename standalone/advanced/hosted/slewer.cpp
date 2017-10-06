#include "slewer.h"

Slewer::Slewer(QWidget *parent):
    QWidget(parent)
{

    timer = new QTimer(this);
    position = 0;
    velocity = 0;

    lastOutput = -1;

    connect(timer, SIGNAL(timeout()), this, SLOT(slotUpdate()));

}

void Slewer::slotSlew(double target, double time)
{
    if(target != destination)   //If new destination update velocity
    {
        destination = target;

        velocity = (destination - position)/time;

        if(!timer->isActive())
        {
            timer->start(1);
        }
    }
}

void Slewer::slotUpdate()
{
    if((int)position < (int)destination || (int)position > (int)destination) //Not using != here because of rounding/casting. Could cause erroneuous jump @ high velocities.
    {
        position += velocity;
    }
    else
    {
        timer->stop();
    }

    if(lastOutput != (int)position)
    {
        emit signalOutput(position);
        lastOutput = position;
    }


}

