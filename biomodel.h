#ifndef BIOMODEL_H
#define BIOMODEL_H

#include <string>
#include "Windows.h"
#include <QFileDialog>

class BioModel
{
public:
    void addFile(QString);
    void deleteFile(QString);
    void sysCommandTest();
    void generateKey();
    void encryptFiles();
    void decryptFiles();
    void initializeDirectory();
    void addFolder(QString);

private:
    std::string getCurrDirectory();
};

#endif // BIOMODEL_H
