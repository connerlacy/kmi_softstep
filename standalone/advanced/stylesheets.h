#ifndef STYLESHEETS_H
#define STYLESHEETS_H

#include <QString>
#include <QFile>
#include <QTextStream>

class StyleSheets
{

    public:
        StyleSheets();

        QFile* file;

        /*QString modlineEnable1StyleSheet;
        QString modlineEnable2StyleSheet;
        QString modlineEnable3StyleSheet;
        QString modlineEnable4StyleSheet;
        QString modlineEnable5StyleSheet;
        QString modlineEnable6StyleSheet;*/

        //Could also use an array here, but QList is handy and good to know how to use
        QList<QString> modlineEnableStyleSheet;
        QList<QString> keyBoxOpenButtonStyleSheet;
        QString keyBoxSelectedStyleSheet;
        QString keyBoxNotSelectedStyleSheet;
        QString deviceStyleSheet;

};

#endif // STYLESHEETS_H
