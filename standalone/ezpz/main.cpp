#include <QApplication>
#include "mainwindow.h"

#include<stdio.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("SoftStep Basic Editor");
    w.setFixedSize(w.size());
    w.show();
    return a.exec();
}
