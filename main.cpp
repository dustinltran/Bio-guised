#include "mainwindow.h"
#include <QApplication>
#include "Windows.h"
#include "biomodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    BioModel* bioModel = new BioModel(); //Need for use of functions from biomodel
    bioModel->initializeDirectory();
    return a.exec();
}
