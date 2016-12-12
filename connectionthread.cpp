#include "connectionthread.h"
#include <QtSerialPort/QtSerialPort>
#include <QTime>

ConnectionThread::ConnectionThread()
{

}
void ConnectionThread::run()
{
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
            delay(5000);
        }
        else{
            bioGuised->hide();
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
