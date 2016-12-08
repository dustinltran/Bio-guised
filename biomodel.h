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
    void createNewFileFolder(QString);
    void unhideFile(QString, QString);
    void unhideFolder(QString, QString);
    std::string getCurrDirectory();

private:   
    std::wstring stringToLPCWSTR(const std::string);
    LPWSTR stringToLPWSTR(std::string string);
    void runProcess(LPWSTR cmd);
};

#endif // BIOMODEL_H
