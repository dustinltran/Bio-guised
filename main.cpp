#include "mainwindow.h"
#include <QApplication>
#include <QtSerialPort/QtSerialPort>
#include "Windows.h"
#include "biomodel.h"
#include "bioguised.h"
#include "thread"

//BioGuised *bioGuised = new BioGuised();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::thread watchdog(watchdog);

    MainWindow w;
    w.show();

    std::thread watchdog(watchdog);
    BioModel* bioModel = new BioModel(); //Need for use of functions from biomodel
    ;


    return a.exec();
}

void watchdog(){
    QSerialPort *availableport;


}

