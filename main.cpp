#include "mainwindow.h"
#include <QApplication>
#include "Windows.h"
#include "biomodel.h"
#include "bioguised.h"
#include "thread"
#include "connectionthread.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    BioModel* bioModel = new BioModel(); //Need for use of functions from biomodel
    bioModel->generateKey();
    bioModel->initializeDirectory();
    
    return a.exec();
}

