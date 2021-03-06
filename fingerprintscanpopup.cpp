#include "fingerprintscanpopup.h"
#include "ui_fingerprintscanpopup.h"
#include "connectionthread.h"
#include <QtSerialPort/QtSerialPort>
#include <QTime>

FingerprintScanPopup::FingerprintScanPopup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FingerprintScanPopup)
{
    ui->setupUi(this);
}



FingerprintScanPopup::~FingerprintScanPopup()
{
    delete ui;
}


bool FingerprintScanPopup::registerPrint(int print){
    char fingerPrint[4];
    int retry = 0, bytes_available;
    bool read = false;
    QSerialPortInfo info("COM6");
    // Check info of the port
    qDebug() << "Name        : " << info.portName();
    qDebug() << "Manufacturer: " << info.manufacturer(); //if showing manufacturer, means Qstring &name is good
    qDebug() << "Busy: " << info.isBusy() << endl;

    // Initialize Serial
    QSerialPort serial;
    serial.setPortName("COM6");
    serial.open(QIODevice::ReadWrite);
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    if (serial.isOpen() && serial.isWritable())
    {
        qDebug() << "Is open : " << serial.isOpen() << endl;
        qDebug() << "Is writable : " << serial.isWritable() << endl;

        QByteArray action("r");
        serial.write(action);
        delay(500);
        itoa(print, fingerPrint, 10);
        strncat(fingerPrint, "\n", 1);
        QByteArray finger(fingerPrint);

        //Prevent race condition
        while(retry < 3 && (serial.isOpen() && serial.isWritable())){
            serial.write(finger);
            delay(500);
            retry++;
        }
        if(retry >= 3){

            //Send Alert
        }
        retry = 0;

                serial.waitForReadyRead(20000);
                bytes_available = serial.bytesAvailable();

            QByteArray byte_array = serial.read(bytes_available);
            char *rawData = byte_array.data();
            qDebug() << *rawData;
            if((int)*rawData != -1)
                         bool read = true;

           qDebug() << read;

        if(serial.flush())
            {
                qDebug() << "ok" << endl;

            }
            qDebug() <<"value sent!!! "<< endl;
            serial.close();
    }

    else
    {

        qDebug() << "An error occured" << endl;
    }
    retry = 0;
    this->close();
    return read;
}

void FingerprintScanPopup::delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}
