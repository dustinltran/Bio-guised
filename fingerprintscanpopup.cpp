#include "fingerprintscanpopup.h"
#include "ui_fingerprintscanpopup.h"

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
