#include "mainwindow.h"
#include <QApplication>
#include <QtSerialPort/QtSerialPort>
#include "Windows.h"
#include "biomodel.h"
#include "bioguised.h"

//BioGuised *bioGuised = new BioGuised();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    BioModel* bioModel = new BioModel(); //Need for use of functions from biomodel
    ;
    return a.exec();
 }
