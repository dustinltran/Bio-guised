#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bioguised.h"
#include "fingerprintscanpopup.h"

FingerprintScanPopup fingerprints[10] = new FingerprintScanPopup();

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

    fingerprints[0].registerPrint(0);
    fingerprints[0].show();
}

void MainWindow::on_RegisterButton_clicked()
{
    MainWindow::close();
    BioGuised *bioGuised = new BioGuised();
    bioGuised->show();
}

void MainWindow::on_RPinky_clicked()
{

}
