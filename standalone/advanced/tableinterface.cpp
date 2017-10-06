#include <QQuickView>
#include <QQuickItem>
#include <QQmlContext>
#include <QQuickWidget>
#include "tableinterface.h"


TableInerface::TableInerface(QWidget *parent) :
    QWidget(parent)
{
    //Make Window a Tool Window, Set Size
    this->setWindowFlags(Qt::Widget);
    this->setFixedSize(114,114);
    //this->setWindowTitle("Tables");

    //-------- Setup Ui
    QWidget *uiWidget = new QWidget(this);
    pedalLiveTableForm.setupUi(uiWidget);

    //-------- Setup QML Ui
    qmlWidget = new QWidget(uiWidget);

    QQuickWidget* qmlView = new QQuickWidget;
    qmlView->setSource(QUrl("qrc:/CalibrationTable.qml"));

    qmlView->rootContext()->setContextProperty("TableInterface", this);

    QVBoxLayout *layout = new QVBoxLayout(qmlWidget);
    layout->addWidget(qmlView);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setStretch(0,0);

    //Set Root object for function access
    rootObject = qmlView->rootObject();
    //Get Access to multislider block objects within
    blocks =  qmlView->rootObject()->findChildren<QObject *>("block");

    this->show();

    //QMetaObject::invokeMethod(rootObject, "clearBlocks");
}

void TableInerface::slotDrawTable(float x, float y, float width)
{
    ///qDebug() << "============================================================= DRAW TABLE" << x << y << width;

    //QMetaObject::invokeMethod(rootObject, "clearBlocks");
    QMetaObject::invokeMethod(rootObject, "drawBlock", Q_ARG(QVariant, x), Q_ARG(QVariant, y), Q_ARG(QVariant, width));

    /*for(int i = 0; i < table.length(); i++)
    {
        //QMetaObject::invokeMethod(rootObject, "clearBlocks");
        //QMetaObject::invokeMethod(rootObject, "drawBlock", Q_ARG(QVariant, i), Q_ARG(QVariant, table.at(i)), Q_ARG(QVariant, table.length()/114));
    }*/
}

void TableInerface::slotClearTable()
{
    //qDebug() << "-------------- clear pedal table on load";
    QMetaObject::invokeMethod(rootObject, "clearBlocks");
}

void TableInerface::slotDrawLinear()
{
    QMetaObject::invokeMethod(rootObject, "drawLinear");
}
