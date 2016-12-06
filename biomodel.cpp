#include "biomodel.h"
#include "Windows.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <iomanip>

/*
    addFile: Allows one to add a file to a directory.
*/
void BioModel::addFile(QString source)
{
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];

    _splitpath_s(source.toStdString().c_str(), drive, dir, fname, ext);

    std::string outputDirectory = getCurrDirectory() + "\\bioguised";

    if(CreateDirectoryA(outputDirectory.c_str(), NULL) ||
            ERROR_ALREADY_EXISTS == GetLastError()){
        std::stringstream stringStream;
        stringStream << outputDirectory << "\\" << fname << ext;
        std::string newFileLocation = stringStream.str();
        LPCSTR destination = newFileLocation.c_str();
        BOOL b = MoveFileA(source.toStdString().c_str(), destination);
        if(!b){
            GetLastError();
        } else {
            printf("Success!!!!!!!!");
        }
    } else {
        printf("Destination File does not exist");
    }

}

/*
    deleteFile: Allows one to delete a file.
*/
void BioModel::deleteFile(QString filePath)
{
    std::string filePathString = filePath.toLocal8Bit().constData();

    if(_unlink(filePathString.c_str()) == -1){
        std::perror("Error when deleting file!");
    }
}

void BioModel::addFolder(QString folderToMove)
{
    std::string source = folderToMove.toUtf8().toStdString();
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];

    _splitpath_s(source.c_str(), drive, dir, fname, ext);

    std::string destination = getCurrDirectory() + "\\bioguised-testfolder" + "\\" + fname;

    std::cout << "Source" << source << std::endl;
    std::cout << "Destination" << destination << std::endl;

    if(!MoveFileExA(source.c_str(), destination.c_str(), MOVEFILE_WRITE_THROUGH)){
        printf ("addFolder failed with error %d\n", GetLastError());
        return;
    }
}
void BioModel::initializeDirectory(){
    std::string storageDirectory = getCurrDirectory() + "\\bioguised-testfolder";
    if(CreateDirectoryA(storageDirectory.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()){
        std::cout << "Directory Initialized" << std::endl;
    } else {
        std::cout << "Problem Initializing Directory" << std::endl;
    }
}

std::string BioModel::getCurrDirectory(){
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}

void BioModel::sysCommandTest(){
    std::string cPath = getCurrDirectory();
    std::string filePath = cPath + "\\bioguised-testfolder";
    printf(filePath.c_str());
    printf("\n");
    std::string exeCrypto = cPath + "\\Win32Project2.exe k " + cPath;
    std::cout << exeCrypto.c_str() << std::endl;
//    std::system(exeCrypto.c_str());
    WinExec(exeCrypto.c_str(), SW_SHOW);
    return;
}

void BioModel::generateKey(){
    std::string currPath = getCurrDirectory();
    std::string execmd = currPath + "\\Win32Project2.exe k " + currPath;

    if(WinExec(execmd.c_str(), SW_HIDE) <= 31){
        std::perror("Invalid Command");
    }
    return;
}

void BioModel::encryptFiles(){
    std::string currPath = getCurrDirectory();
    std::string execmd = currPath + "\\Win32Project2.exe e " + currPath + "\\bioguised-testfolder";

    if(WinExec(execmd.c_str(), SW_HIDE) <= 31){
        std::perror("Invalid Command");
    }
    return;
}

void BioModel::decryptFiles(){
    std::string currPath = getCurrDirectory();
    std::string execmd = currPath + "\\Win32Project2.exe d " + currPath + "\\bioguised-testfolder";

    if(WinExec(execmd.c_str(), SW_HIDE) <= 31){
        std::perror("Invalid Command");
    }
    return;
}

void BioModel::encryptKey(std::string K_KEY){
    std::string currPath = getCurrDirectory();
    std::string execmd = currPath + "\\Win32Project2.exe x " + currPath + " " + K_KEY;

    if(WinExec(execmd.c_str(), SW_HIDE) <= 31){
        std::perror("Invalid Command");
    }
    return;
}

void BioModel::decryptKey(std::string K_KEY){
    std::string currPath = getCurrDirectory();
    std::string execmd = currPath + "\\Win32Project2.exe y " + currPath + " " +  K_KEY;

    if(WinExec(execmd.c_str(), SW_HIDE) <= 31){
        std::perror("Invalid Command");
    }
    return;
}
