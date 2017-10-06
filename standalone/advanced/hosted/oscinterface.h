#ifndef OSCINTERFACE_H
#define OSCINTERFACE_H

#include <QObject>
#include <QVariant>
#include <QtNetwork/QUdpSocket>


class OscInterface : public QObject
{
    Q_OBJECT
public:
    explicit OscInterface(QObject *parent = 0);

    QUdpSocket *socket;

    QString         msgAddress;
    QString         msgType;
    unsigned char   msgVal[4];

    int             inputPort;
    int             outputPort;

    QString         ip;

    bool oscEnabled[8];
    QString oscAddressTag[8];
    int oscInputVal[8];
    
signals:
    void signalSendOscMessageToSource(int sourceNum, int val);
    void signalSetOSCDisplayValue(int inputNum, int val);
    
public slots:
    void slotReadPendingDatagrams();
    void slotWriteDatagram(QString tag, int val);

    void slotDistributeReceivedMessage(QString tag, int val);

    void slotSetInputEnable(int inputNum, bool enabled);
    void slotSetOSCAddressTags(int inputNum, QString tag);
    void slotSetOutputPort(int port);
    void slotSetInputPort(int port);
    void slotSetOutputIPAddress(QString ipString);




    
};

#endif // OSCINTERFACE_H
