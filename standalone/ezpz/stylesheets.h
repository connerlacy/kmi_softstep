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

    QString sendButtonDirtyStyleSheet;
    QString sendButtonCleanStyleSheet;
    QString sendButtonDirtyStyleSheet_windows;
    QString sendButtonCleanStyleSheet_windows;
};

#endif // STYLESHEETS_H
