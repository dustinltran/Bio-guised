#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bioguised.h"
#include "fingerprintscanpopup.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LPinky_clicked()
{
    FingerprintScanPopup *fingerprintScanPopup = new FingerprintScanPopup();
    fingerprintScanPopup->show();
}

void MainWindow::on_RegisterButton_clicked()
{
    BioGuised *bioGuised = new BioGuised();
    bioGuised->show();
}
