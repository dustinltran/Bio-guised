#include "bioguised.h"
#include "ui_bioguised.h"
#include "biomodel.h"
#include <iostream>
#include <QFileDialog>

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
