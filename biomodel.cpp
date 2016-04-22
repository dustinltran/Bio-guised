#include "biomodel.h"
#include "Windows.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>


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

    std::string outputDirectory = getCurrDirectory() + "\\bioguised-testfolder";

    if(CreateDirectoryA(outputDirectory.c_str(), NULL) ||
            ERROR_ALREADY_EXISTS == GetLastError()){
        std::stringstream ss;
        ss << outputDirectory << "\\" << fname << ext;
        std::string s = ss.str();
        LPCSTR destination = s.c_str();
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
void BioModel::deleteFile()
{

}

std::string BioModel::getCurrDirectory(){
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}

