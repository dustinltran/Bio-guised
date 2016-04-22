#ifndef BIOMODEL_H
#define BIOMODEL_H

#include <string>
#include "Windows.h"
#include <QFileDialog>

class BioModel
{
public:
    void addFile(QString);
    void deleteFile();

private:
    std::string getCurrDirectory();
};

#endif // BIOMODEL_H
