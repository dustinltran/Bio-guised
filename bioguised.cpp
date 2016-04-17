#include "bioguised.h"
#include "ui_bioguised.h"

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
