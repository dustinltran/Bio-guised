#include "fingerprintscanpopup.h"
#include "ui_fingerprintscanpopup.h"

#include <QtSerialPort/QtSerialPort>

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





FingerprintScanPopup::registerPrint(int print){
    char fingerPrint[4];
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

    if (serial.isWritable())
    {
        qDebug() << "Is open : " << serial.isOpen() << endl;
        qDebug() << "Is writable : " << serial.isWritable() << endl;

        fingerPrint = itoa(print, fingerPrint, 10);
        fingerPrint = strncat(fingerPrint, "\n", 1);
        QByteArray finger(fingerPrint);
        serial.write(finger);
        if (serial.bytesToWrite() > 0)
        {
            serial.flush();
            if(serial.waitForBytesWritten(1000))
            {
                qDebug() << "data has been send" << endl;
            }

        }
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
}
