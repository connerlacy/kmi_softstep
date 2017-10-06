#include "stylesheets.h"
#include <QDebug>

StyleSheets::StyleSheets()
{


    //------ Mac Send Button
    //Dirty
    file = new QFile(":/resources/sendbuttondirtystylesheet.qss");
    if(file->open(QIODevice::ReadOnly))
    {
        sendButtonDirtyStyleSheet = QTextStream(file).readAll();
        //qDebug() << sendButtonDirtyStyleSheet;
    }

    file->close();

    //Clean
    file = new QFile(":/resources/sendbuttoncleanstylesheet.qss");
    if(file->open(QIODevice::ReadOnly))
    {
        sendButtonCleanStyleSheet = QTextStream(file).readAll();
        //qDebug() << sendButtonCleanStyleSheet;
    }

    file->close();

    //------ Windows Send Button
    //Dirty
    file = new QFile(":/resources/sendbuttondirtystylesheet_windows.qss");
    if(file->open(QIODevice::ReadOnly))
    {
        sendButtonDirtyStyleSheet_windows = QTextStream(file).readAll();
        //qDebug() << QString("win dirty style") << sendButtonDirtyStyleSheet_windows;
    }

    file->close();

    //Clean
    file = new QFile(":/resources/sendbuttoncleanstylesheet_windows.qss");
    if(file->open(QIODevice::ReadOnly))
    {
        sendButtonCleanStyleSheet_windows = QTextStream(file).readAll();
        //qDebug()<< QString("win clean style") << sendButtonCleanStyleSheet_windows;
    }

    file->close();
}
