#include "connectionthread.h"
#include <QtSerialPort/QtSerialPort>
#include <QtCore>
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
            while(!serial.isWritable());
            QByteArray index("v");
            serial.write(index);
            do{
                serial.waitForReadyRead(1000);
                bytes_available = serial.bytesAvailable();
            }while(bytes_available <= 0);

            QByteArray byte_array = serial.read(bytes_available);
            qDebug() << byte_array;

            char *rawData = byte_array.data();
            int data = (int)*rawData;

            if(data > 0 )
            bioGuised->show();
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
