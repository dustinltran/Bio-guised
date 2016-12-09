#include "biomodel.h"
#include "Windows.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <iomanip>

/****************************************************************************************
TASK:   Add a file to the hidden directory
PRE :   source - source of the file to add
POST:   File has been added to hidden directory
****************************************************************************************/
void BioModel::addFile(QString source)
{
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];

    _splitpath_s(source.toStdString().c_str(), drive, dir, fname, ext);

    std::string outputDirectory = getCurrDirectory() + "\\bioguised-testfolder";

    if(CreateDirectoryA(outputDirectory.c_str(), NULL) ||
            ERROR_ALREADY_EXISTS == GetLastError()){
        std::stringstream stringStream;
        stringStream << outputDirectory << "\\" << fname << ext;
        std::string newFileLocation = stringStream.str();
        LPCSTR destination = newFileLocation.c_str();
        BOOL successful = MoveFileA(source.toStdString().c_str(), destination);
        if(!successful){
            GetLastError();
        } else {
            printf("Success!!!!!!!!");
        }
    } else {
        printf("Destination File does not exist");
    }

}

/****************************************************************************************
TASK:   Create a new hidden directory within main hidden directory
PRE :   newFolderName - Name for new folder
POST:   new folder with specified name is created
****************************************************************************************/
void BioModel::createNewFileFolder(QString newFolderName){
    std::string destination = newFolderName.toUtf8().toStdString();
    if(CreateDirectoryA(destination.c_str(), NULL)
            || ERROR_ALREADY_EXISTS == GetLastError()){
        std::cout << "Directory Initialized" << std::endl;
        if(SetFileAttributesA(destination.c_str(), FILE_ATTRIBUTE_HIDDEN)){
            std::cout << "Directory Attribute Set" << std::endl;
        } else {
            std::cout << "Problem Assigning Attribute to Directory"
                      << GetLastError() << std::endl;
        }
    } else {
        std::cout << "Problem Initializing Directory" << GetLastError() << std::endl;
    }
}

/****************************************************************************************
TASK:   Delete a target file
PRE :   filePath - source of file to be deleted
POST:   file is deleted
****************************************************************************************/
void BioModel::deleteFile(QString filePath)
{
    std::string filePathString = filePath.toLocal8Bit().constData();

    if(_unlink(filePathString.c_str()) == -1){
        std::perror("Error when deleting file!");
    }
}

/****************************************************************************************
TASK:   Add folder to hidden directory
PRE :   folderToMove - filePath of folder to be added to directory
POST:   Folder and all contents added to hidden directory
****************************************************************************************/
void BioModel::addFolder(QString folderToMove)
{
    std::string destination;
    std::string source = folderToMove.toUtf8().toStdString();
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];

    _splitpath_s(source.c_str(), drive, dir, fname, ext);

    destination = getCurrDirectory() + "\\bioguised-testfolder" + "\\" + fname;

    if(!MoveFileExA(source.c_str(), destination.c_str(), MOVEFILE_WRITE_THROUGH)){
        printf ("addFolder failed with error %d\n", GetLastError());
        return;
    }
}

/****************************************************************************************
TASK:   Initializes the base hidden directory
PRE :   N/A
POST:   Base hidden directory created
****************************************************************************************/
void BioModel::initializeDirectory(){
    std::string storageDirectory = getCurrDirectory() + "\\bioguised-testfolder";

    if(CreateDirectoryA(storageDirectory.c_str(), NULL)
            || ERROR_ALREADY_EXISTS == GetLastError()){
        std::cout << "Directory Initialized" << std::endl;
        if(SetFileAttributesA(storageDirectory.c_str(), FILE_ATTRIBUTE_HIDDEN)){
            std::cout << "Directory Attribute Set" << std::endl;
        }
    } else {
        std::cout << "Problem Initializing Directory" << std::endl;
    }
}

/****************************************************************************************
TASK:   Retrieve current exe directory
PRE :   N/A
POST:   returns filepath to current directory
****************************************************************************************/
std::string BioModel::getCurrDirectory(){
    char path[MAX_PATH];
    GetModuleFileNameA(NULL, path, MAX_PATH);
    std::string::size_type dir = std::string(path).find_last_of("\\/");

    return std::string(path).substr(0, dir);
}

/****************************************************************************************
TASK:   convert a std::string to LPWSTR
PRE :   string - string to be converted
POST:   returns string as LPWSTR
****************************************************************************************/
LPWSTR BioModel::stringToLPWSTR(std::string string){
    wchar_t *wtext = new wchar_t[strlen(string.c_str()) * 2];
    mbstowcs(wtext, string.c_str(), strlen(string.c_str()) + 1);
    LPWSTR lpwstrExecmd = wtext;

    return lpwstrExecmd;
}

/****************************************************************************************
TASK:   Generate a key for file encrption
PRE :   N/A
POST:   Key is Generated
****************************************************************************************/
void BioModel::generateKey(){
    std::string currPath = getCurrDirectory();
    std::string execmd = currPath + "\\Win32Project2.exe k " + currPath;
    LPWSTR lpwstrExecmd = stringToLPWSTR(execmd);

    runProcess(lpwstrExecmd);
}

/****************************************************************************************
TASK:   Encrypt files in hidden directory
PRE :   N/A
POST:   Files are encrpyted
****************************************************************************************/
void BioModel::encryptFiles(){
    std::string currPath = getCurrDirectory();
    std::string execmd = currPath + "\\Win32Project2.exe e " +
            currPath + "\\bioguised-testfolder";
    LPWSTR lpwstrExecmd = stringToLPWSTR(execmd);

    runProcess(lpwstrExecmd);
}

/****************************************************************************************
TASK:   Decrypt files in hidden directory
PRE :   N/A
POST:   Files are decrypted
****************************************************************************************/
void BioModel::decryptFiles(){
    std::string currPath = getCurrDirectory();
    std::string execmd = currPath + "\\Win32Project2.exe d " +
            currPath + "\\bioguised-testfolder";
    LPWSTR lpwstrExecmd = stringToLPWSTR(execmd);

    runProcess(lpwstrExecmd);
}

/****************************************************************************************
TASK:   Encrypt key used for file encryption/decryption
PRE :   K_KEY - key used to encrypt key
POST:   key is encrypted
****************************************************************************************/
void BioModel::encryptKey(std::string K_KEY){
    std::string currPath = getCurrDirectory();
    std::string execmd = currPath + "\\Win32Project2.exe x " + currPath + " " + K_KEY;
    LPWSTR lpwstrExecmd = stringToLPWSTR(execmd);

    runProcess(lpwstrExecmd);
}

/****************************************************************************************
TASK:   Decrypt key used for file encryption/decryption
PRE :   K_KEY - key used to decrypt key
POST:   key is decrypted
****************************************************************************************/
void BioModel::decryptKey(std::string K_KEY){
    std::string currPath = getCurrDirectory();
    std::string execmd = currPath + "\\Win32Project2.exe y " + currPath + " " +  K_KEY;
    LPWSTR lpwstrExecmd = stringToLPWSTR(execmd);

    runProcess(lpwstrExecmd);
}

/****************************************************************************************
TASK:   Execute a command and wait for process to finish.
PRE :   cmd - command to be executed
POST:   cmd has finished execution
CITATION: The following function was heavily influenced by the following source
    https://msdn.microsoft.com/en-us/library/windows/desktop/ms682512(v=vs.85).aspx
****************************************************************************************/
void BioModel::runProcess(LPWSTR cmd){
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory (&pi, sizeof(pi));

    if(!CreateProcess(NULL, cmd, NULL, NULL, FALSE, CREATE_NO_WINDOW,
                      NULL, NULL, &si, &pi)){
        printf("CreateProcess failed %d.\n", GetLastError());
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

/****************************************************************************************
TASK:   unhides file from hidden folder
PRE :   from - location of file to be moved
        to - location for file to be moved to
POST:   file moved to new location
****************************************************************************************/
void BioModel::unhideFile(QString from, QString to){
    //TODO: Code for unhiding a file
    std::string source = from.toUtf8().toStdString();
    std::string destination;
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];

    _splitpath_s(source.c_str(), drive, dir, fname, ext);

    destination = to.toUtf8().toStdString() + "\\" + fname + ext;

    if(!MoveFileA(source.c_str(), destination.c_str())){
        printf ("unhideFile failed with error %d\n", GetLastError());
    }
}

/****************************************************************************************
TASK:   unhides application folder from hidden folder
PRE :   from - location of folder to be moved
        to - location for folder to be moved to
POST:   folder moved to new location
****************************************************************************************/
void BioModel::unhideFolder(QString from, QString to){
    //TODO: Code for unhiding a folder
    std::string destination;
    std::string source = from.toUtf8().toStdString();
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];

    _splitpath_s(source.c_str(), drive, dir, fname, ext);

    destination = to.toUtf8().toStdString() + "\\" + fname;

    if(!MoveFileExA(source.c_str(), destination.c_str(), MOVEFILE_WRITE_THROUGH)){
        printf ("unhideFolder failed with error %d\n", GetLastError());
    }
}
