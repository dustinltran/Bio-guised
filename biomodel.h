#ifndef BIOMODEL_H
#define BIOMODEL_H

#include <string>
#include "Windows.h"
class BioModel
{
public:
    void addFile(LPCWSTR);
    void deleteFile();
};

#endif // BIOMODEL_H
