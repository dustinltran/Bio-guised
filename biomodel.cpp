#include "biomodel.h"
#include "Windows.h"
#include <string>


/*
    addFile: Allows one to add a file to a directory.
*/
void BioModel::addFile(LPCWSTR source)
{
    LPCWSTR destination = L"C:\\Users\\smllt\\Desktop\\test\\test.txt";
    BOOL b = MoveFile(source, destination);
    if(!b){
        GetLastError();
    } else {

    }
}
/*
    deleteFile: Allows one to delete a file.
*/
void BioModel::deleteFile()
{

}

