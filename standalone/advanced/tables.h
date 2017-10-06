#ifndef TABLES_H
#define TABLES_H

#include <QWidget>
#include <QMap>

class Tables : public QWidget
{
    Q_OBJECT
public:
    explicit Tables(QWidget *parent = 0);

    QMap<QString, unsigned char *> tableMap;

    signals:
    
public slots:
    
};

#endif // TABLES_H
