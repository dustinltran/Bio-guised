#include "bioguised.h"
#include "ui_bioguised.h"
#include "biomodel.h"
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
    //printf(sourceFile.toStdString().c_str());
    LPCWSTR srcFile = (const wchar_t*)sourceFile.utf16();

    BioModel* bioModel = new BioModel();
    bioModel->addFile(srcFile);

}
