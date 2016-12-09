#include "mainwindow.h"
#include <QApplication>
#include <QtSerialPort/QtSerialPort>
#include <QTime>
#include "Windows.h"
#include "biomodel.h"
#include "bioguised.h"
#include "thread"

//BioGuised *bioGuised = new BioGuised();
void delay(int);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    
   //DEBUG std::thread watchdog(watchdog);
    BioModel* bioModel = new BioModel(); //Need for use of functions from biomodel

    
    
    return a.exec();
}

void watchdog(){
    QSerialPort availableport;
    while(true){
        availableport.setPortName("COM6");
        availableport.open(QIODevice::ReadOnly);
        availableport.setBaudRate(QSerialPort::Baud9600);
        availableport.setDataBits(QSerialPort::Data8);
        availableport.setParity(QSerialPort::NoParity);
        availableport.setStopBits(QSerialPort::OneStop);
        availableport.setFlowControl(QSerialPort::NoFlowControl);

        if(availableport.isOpen()){
            //DEBUG MODE ON
            delay(3000);
        }
        else{
            //DEBUG ON
        }
    }

}
void delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}
