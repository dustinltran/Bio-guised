#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bioguised.h"
#include "fingerprintscanpopup.h"
#include <QMessageBox>
#include <QtSerialPort/QtSerialPort>
#include <QCloseEvent>
#include "stdio.h"

FingerprintScanPopup *fingerprints;
bool positions[10] = {false};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
    QByteArray fingerInput;
    char buffer[5];
    int i;
    fingerprints = new FingerprintScanPopup[10];

    for(i = 0; i < FINGERS && positions[i] == false; i++){
        if(positions[i]){
            on_RegisterButton_clicked();
        }
    }
    // Initialize Serial
    QSerialPort serial;
    serial.setPortName("COM6");
    serial.open(QIODevice::ReadWrite);
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

//    for(i = 0; i < FINGERS; i++){
//        while(!serial.isWritable());
//        QByteArray index("n");
//        serial.write(index);

//        fingerInput.prepend("\0");
//        qDebug() << fingerInput.data();
//        while(!serial.isReadable());
       // printf("%s", serial.readAll().data());
    qDebug() << serial.readAll().data();
 //   memcpy(positions,)
//        if(*fingerInput.data() != '\n'){
//            positions[i] = true;
//            qDebug() << positions[i];
//        }

//    }

    for(i = 0; i < FINGERS && positions[i] == false; i++){
        if(positions[i]){
            on_RegisterButton_clicked();
        }
    }
    if(serial.flush())
        {
            qDebug() << "ok" << endl;
        }
    qDebug() <<"value sent!!! "<< endl;
    serial.close();
        ui->setupUi(this);


    }

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::closeEvent (QCloseEvent *event)
{
//    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "",
//                                                                tr("Are you sure?\n"),
//                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
//                                                                QMessageBox::Yes);
//    if (resBtn != QMessageBox::Yes) {
//        event->ignore();
//    } else {
//        event->accept();
//    }
    MainWindow::showMinimized();
}

void MainWindow::on_RegisterButton_clicked()
{
    int i;
    for(i = 0; i < FINGERS && positions[i] == false; i++){
        if((i == (FINGERS - 1)) && positions[i] == false){
            QMessageBox::warning(this, tr("Bio-guised"),
                                           tr("Please register at least 1 fingerprint"),
                                           QMessageBox::Ok);
            return;
        }
    }
    MainWindow::close();
    BioGuised *bioGuised = new BioGuised();
    bioGuised->show();
}


void MainWindow::on_LPinky_clicked()
{
    bool read;
    read = fingerprints[0].registerPrint(0);
    fingerprints[0].show();
    if (read == true){
        positions[0] = true;
        QPixmap pixmap(".\fingerprint.jpg");
        QIcon ButtonIcon(pixmap);
        ;
    }
}

void MainWindow::on_LRing_clicked()
{
    bool read;
    read = fingerprints[1].registerPrint(0);
    fingerprints[1].show();
    if (read == true){
        positions[1] = true;
        QPixmap pixmap(".\fingerprint.jpg");
        QIcon ButtonIcon(pixmap);
    }
}

void MainWindow::on_LMiddle_clicked()
{
    bool read;
    read = fingerprints[2].registerPrint(0);
    fingerprints[2].show();
    if (read == true){
        positions[2] = true;
        QPixmap pixmap(".\fingerprint.jpg");
        QIcon ButtonIcon(pixmap);
        ;
    }
}

void MainWindow::on_LIndex_clicked()
{
    bool read;
    read = fingerprints[3].registerPrint(0);
    fingerprints[3].show();
    if (read == true){
        positions[3] = true;
        QPixmap pixmap(".\fingerprint.jpg");
        QIcon ButtonIcon(pixmap);
        ;
    }
}

void MainWindow::on_LThumb_clicked()
{
    bool read;
    read = fingerprints[5].registerPrint(0);
    fingerprints[5].show();
    if (read == true){
        positions[5] = true;
        QPixmap pixmap(".\fingerprint.jpg");
        QIcon ButtonIcon(pixmap);
        ;
    }

}

void MainWindow::on_RThumb_clicked()
{
    bool read;
    read = fingerprints[6].registerPrint(0);
    fingerprints[6].show();
    if (read == true){
        positions[6] = true;
        QPixmap pixmap(".\fingerprint.jpg");
        QIcon ButtonIcon(pixmap);
        ;
    }

}

void MainWindow::on_RIndex_clicked()
{
    bool read;
    read = fingerprints[6].registerPrint(0);
    fingerprints[6].show();
    if (read == true){
        positions[6] = true;
        QPixmap pixmap(".\fingerprint.jpg");
        QIcon ButtonIcon(pixmap);
        ;
    }
}

void MainWindow::on_RMiddle_clicked()
{
    bool read;
    read = fingerprints[7].registerPrint(0);
    fingerprints[7].show();
    if (read == true){
        positions[7] = true;
        QPixmap pixmap(".\fingerprint.jpg");
        QIcon ButtonIcon(pixmap);
        ;
    }

}

void MainWindow::on_RRing_clicked()
{
    bool read;
    read = fingerprints[8].registerPrint(0);
    fingerprints[8].show();
    if (read == true){
        positions[8] = true;
        QPixmap pixmap(".\fingerprint.jpg");
        QIcon ButtonIcon(pixmap);
        ;
    }

}

void MainWindow::on_RPinky_clicked()
{
    bool read;
    read = fingerprints[9].registerPrint(0);
    fingerprints[9].show();
    if (read == true){
        positions[9] = true;
        QPixmap pixmap(".\fingerprint.jpg");
        QIcon ButtonIcon(pixmap);
        ;
    }
}

