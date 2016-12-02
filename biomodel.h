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
    void encryptKey(std::string);
    void decryptKey(std::string);

private:
    std::string getCurrDirectory();
    std::wstring stringToLPCWSTR(const std::string);
};

#endif // BIOMODEL_H
