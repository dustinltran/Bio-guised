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



void FingerprintScanPopup::on_Register_clicked()
{

    //Play Video of scanning
}
