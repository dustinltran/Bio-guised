#include "bioguised.h"
#include "ui_bioguised.h"
#include "biomodel.h"
#include <iostream>
#include <QFileDialog>
#include <QInputDialog>

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
/****************************************************************************************
TASK:   Get file to be added
PRE :   N/A
POST:   Selected file added to hidden directory
****************************************************************************************/
void BioGuised::on_addFile_clicked()
{
    const QString DIR = "C:\\";
    QString sourceFile = QFileDialog::getOpenFileName(this,NULL,DIR);

    if(!sourceFile.isEmpty()){
        BioModel* bioModel = new BioModel();
        bioModel->addFile(sourceFile);
    }
}

/****************************************************************************************
TASK:   Get file to be deleted
PRE :   N/A
POST:   Selected File is deleted
****************************************************************************************/
void BioGuised::on_deleteFile_clicked()
{
    BioModel* bioModel = new BioModel();
    std::string path = bioModel->getCurrDirectory();
    const QString DIR = QString::fromStdString(path) + "\\bioguised-testfolder";

    QString fileToDelete = QFileDialog::getOpenFileName(this,NULL, DIR);
    if (!fileToDelete.isEmpty()){
        bioModel->deleteFile(fileToDelete);
    }
}

/****************************************************************************************
TASK:   Get application folder to be added
PRE :   N/A
POST:   Selected folder is added
****************************************************************************************/
void BioGuised::on_addApplication_clicked()
{
    const QString DIR = "C:\\";
    QString folderToMove = QFileDialog::getExistingDirectory(this,NULL,DIR);

    if(!folderToMove.isEmpty()){
        BioModel* bioModel = new BioModel();
        bioModel->addFolder(folderToMove);
    }
}

/****************************************************************************************
TASK:   Get name for new folder
PRE :   N/A
POST:   New folder created with the name input
****************************************************************************************/
void BioGuised::on_createNewFileFolder_clicked()
{
    BioModel* bioModel = new BioModel();
    std::string path = bioModel->getCurrDirectory();

    QString newFolderName = QInputDialog::getText(this, tr("Name New Folder"),
                                                  tr("Name"), QLineEdit::Normal);
    if (!newFolderName.isEmpty()){
       const QString DIR = QString::fromStdString(path) +
                "\\bioguised-testfolder" + "\\" + newFolderName;
        bioModel->createNewFileFolder(DIR);
    }
}

/****************************************************************************************
TASK:   Get file to move and location to move to
PRE :   N/A
POST:   file is moved to new location
****************************************************************************************/
void BioGuised::on_unhideFile_clicked()
{
    BioModel* bioModel = new BioModel();
    std::string path = bioModel->getCurrDirectory();
    const QString fromDIR = QString::fromStdString(path) + "\\bioguised-testfolder";
    const QString toDIR = "C:\\";

    QString fileToUnhide = QFileDialog::getOpenFileName(this,NULL, fromDIR);
    if (!fileToUnhide.isEmpty()){
        QString to = QFileDialog::getExistingDirectory(this,NULL,toDIR);
        if (!to.isEmpty()){
            bioModel->unhideFile(fileToUnhide, to);
        }
    }
}

/****************************************************************************************
TASK:   Get folder to move and location to move to
PRE :   N/A
POST:   folder is moved to new location
****************************************************************************************/
void BioGuised::on_unhideApplication_clicked()
{
    BioModel* bioModel = new BioModel();
    std::string path = bioModel->getCurrDirectory();
    const QString DIR = QString::fromStdString(path) + "\\bioguised-testfolder";
    const QString toDIR = "C:\\";

    QString folderToUnhide = QFileDialog::getExistingDirectory(this,NULL, DIR);
    if (!folderToUnhide.isEmpty()){
        QString toFolder = QFileDialog::getExistingDirectory(this,NULL,toDIR);
        if (!toFolder.isEmpty()){
            bioModel->unhideFolder(folderToUnhide, toFolder);
        }
    }
}
