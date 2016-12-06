#include "bioguised.h"
#include "ui_bioguised.h"
#include "biomodel.h"
#include <iostream>
#include <QtSerialPort/QtSerialPort>
#include <QFileDialog>
#include <QCloseEvent>
#include <QMessageBox>

BioGuised::BioGuised(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BioGuised)
{
    ui->setupUi(this);
}

BioGuised::~BioGuised()
{
    delete ui;
}

void BioGuised::on_addFile_clicked()
{
    QString sourceFile = QFileDialog::getOpenFileName();

    BioModel* bioModel = new BioModel();
    bioModel->addFile(sourceFile);
}

void BioGuised::on_deleteFile_clicked()
{
    QString fileToDelete = QFileDialog::getOpenFileName();

    BioModel* bioModel = new BioModel();
    bioModel->deleteFile(fileToDelete);
}

void BioGuised::on_addApplication_clicked()
{
    QString folderToMove = QFileDialog::getExistingDirectory();

    BioModel* bioModel = new BioModel();
    bioModel->addFolder(folderToMove);
//    std::cout << folderToMove.toUtf8().toStdString() << std::endl;
    // C:/Users/smllt/Documents/Â
}

void BioGuised::closeEvent (QCloseEvent *event)
{
    BioModel *bioModel = new BioModel();
//    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Close App",
//                                                                tr("Are you sure?\n"),
//                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
//                                                                QMessageBox::Yes);
//    if (resBtn != QMessageBox::Yes) {
//        event->ignore();
//    } else {
//        event->accept();
//    }
    bioModel->encryptFiles();
}
