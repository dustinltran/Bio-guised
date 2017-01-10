#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bioguised.h"
#include "biomodel.h"
#include "fingerprintscanpopup.h"
#include "connectionthread.h"
#include <QtCore>
#include <QMessageBox>
#include <QtSerialPort/QtSerialPort>
#include <QCloseEvent>
#include <QTime>
#include <iostream>

FingerprintScanPopup *fingerprints;
BioGuised *bioGuised;
BioModel *biomodel;

bool positions[10] = {false};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    {

    ui->setupUi(this);
    connect(this, SIGNAL(window_loaded()), this, SLOT(gatherInfo()), Qt::ConnectionType(Qt::QueuedConnection | Qt::UniqueConnection));

    }

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::closeEvent (QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
    MainWindow::showMinimized();
}
void MainWindow::showEvent(QShowEvent *ev)
{
    QMainWindow::showEvent(ev);
    emit window_loaded();
}


void MainWindow::gatherInfo(){

    int i, bytes_available;
//    ConnectionThread connection;
    fingerprints = new FingerprintScanPopup[10];
    bioGuised = new BioGuised;
    biomodel = new BioModel;



    // Initialize Serial
    QSerialPort serial;
    serial.setPortName("COM6");
    serial.open(QIODevice::ReadWrite);
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    qDebug() << "connected";

    //delay(500);

    while(!serial.isWritable());
    QByteArray index("n");
    serial.write(index);

    for(int i = 0; i < FINGERS; i++){
        do{
            serial.waitForReadyRead(1000);
            bytes_available = serial.bytesAvailable();
        }while(bytes_available <= 0);

        QByteArray byte_array = serial.read(bytes_available);
       // qDebug() << byte_array;
        char *rawData = byte_array.data();
        int data = (int)*rawData;
        qDebug() << data;
        if(data == 1){
            positions[i] = true;
        }
        else{
            positions[i] = false;
        }


        if(serial.flush())
        {
            qDebug() << "flushed ok" << endl;
        }
    }
    serial.close();
    //std::thread first();
//    connection.start();
    i = 0;
    int flag = 0;
    do{
        if(positions[i] == true){
            on_RegisterButton_clicked();
            flag = 1;
        }
    }while( i < FINGERS && positions[i++] == false && flag == 0);
  //  run();

}
void MainWindow::run()
{
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

            bioGuised->show();
            delay(5000);
        }
        else{
            bioGuised->hide();
        }
    }
}

void MainWindow::on_RegisterButton_clicked()
{
    int bytes_available;
    int i;
    for(i = 0; i < FINGERS && positions[i] == false; i++){
        if((i == (FINGERS - 1)) && positions[i] == false){
            QMessageBox::warning(this, tr("Bio-guised"),
                                           tr("Please register at least 1 fingerprint"),
                                           QMessageBox::Ok);
            return;
        }
    }

    MainWindow::hide();
    QSerialPort serial;
    serial.setPortName("COM6");
    serial.open(QIODevice::ReadWrite);
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    qDebug() << "connected";

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

    delay(2000);
    while(!serial.isWritable());
    QByteArray index2("k");
    serial.write(index2);
    serial.waitForReadyRead(2000);
    bytes_available = serial.bytesAvailable();


    QByteArray byte_array2 = serial.read(bytes_available);
    qDebug() << byte_array2;
    std::string key = byte_array2.toStdString();
    biomodel->encryptKey(key);


    if(data > 0 )
        bioGuised->show();

}


void MainWindow::on_LPinky_clicked()
{
    bool read;
    read = fingerprints[0].registerPrint(0);
     positions[0] = true;
   // fingerprints[0].show();
//    if (read == true){
//        positions[0] = true;
//        QPixmap pixmap(".\fingerprint.jpg");

//    }
     delay(15000);
     gatherInfo();
}

void MainWindow::on_LRing_clicked()
{
    bool read;
    read = fingerprints[1].registerPrint(0);
   // fingerprints[1].show();
    positions[1] = true;
//    if (read == true){
//        positions[1] = true;
//        QPixmap pixmap(".\fingerprint.jpg");
//        QIcon ButtonIcon(pixmap);
//    }
}

void MainWindow::on_LMiddle_clicked()
{
    bool read;
    read = fingerprints[2].registerPrint(0);
     positions[2] = true;
   // fingerprints[2].show();
//    if (read == true){
//        positions[2] = true;
//        QPixmap pixmap(".\fingerprint.jpg");
//        QIcon ButtonIcon(pixmap);
//        ;
//    }
}

void MainWindow::on_LIndex_clicked()
{
    bool read;
    read = fingerprints[3].registerPrint(0);
     positions[3] = true;
 //   fingerprints[3].show();
//    if (read == true){
//        positions[3] = true;
//        QPixmap pixmap(".\fingerprint.jpg");
//        QIcon ButtonIcon(pixmap);
//        ;
//    }
}

void MainWindow::on_LThumb_clicked()
{
    bool read;
    read = fingerprints[4].registerPrint(0);
     positions[4] = true;
 //   fingerprints[5].show();
//    if (read == true){
//        positions[5] = true;
//        QPixmap pixmap(".\fingerprint.jpg");
//        QIcon ButtonIcon(pixmap);
//        ;
//    }

}

void MainWindow::on_RThumb_clicked()
{
    bool read;
    read = fingerprints[5].registerPrint(0);
     positions[5] = true;
  //  fingerprints[6].show();
//    if (read == true){
//        positions[6] = true;
//        QPixmap pixmap(".\fingerprint.jpg");
//        QIcon ButtonIcon(pixmap);
//        ;
//    }

}

void MainWindow::on_RIndex_clicked()
{
    bool read;
    read = fingerprints[6].registerPrint(0);
     positions[6] = true;
//    fingerprints[6].show();
//    if (read == true){
//        positions[6] = true;
//        QPixmap pixmap(".\fingerprint.jpg");
//        QIcon ButtonIcon(pixmap);
//        ;
//    }
}

void MainWindow::on_RMiddle_clicked()
{
    bool read;
    read = fingerprints[7].registerPrint(0);
     positions[7] = true;
 //   fingerprints[7].show();
//    if (read == true){
//        positions[7] = true;
//        QPixmap pixmap(".\fingerprint.jpg");
//        QIcon ButtonIcon(pixmap);
//        ;
//    }

}

void MainWindow::on_RRing_clicked()
{
    bool read;
    read = fingerprints[8].registerPrint(0);
     positions[8] = true;
 //   fingerprints[8].show();
//    if (read == true){
//        positions[8] = true;
//        QPixmap pixmap(".\fingerprint.jpg");
//        QIcon ButtonIcon(pixmap);
//        ;
//    }

}

void MainWindow::on_RPinky_clicked()
{
    bool read;
    read = fingerprints[9].registerPrint(0);
     positions[9] = true;
 //   fingerprints[9].show();
//    if (read == true){
//        positions[9] = true;
//        QPixmap pixmap(".\fingerprint.jpg");
//        QIcon ButtonIcon(pixmap);
//        ;
//    }
}

void MainWindow::delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}


