// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <io.h>
#include <stdio.h>
#include <Windows.h>
#include <string>
#include <queue>
#include "..\cryptopp565\hex.h"
#include "..\cryptopp565\base64.h"
#include "..\cryptopp565\algparam.h"
#include "..\cryptopp565\modes.h"
#include "..\cryptopp565\aes.h"
#include "..\cryptopp565\filters.h"
#include "..\cryptopp565\files.h"
#include "..\cryptopp565\secblock.h"
#include "..\cryptopp565\osrng.h"
#include "..\cryptopp565\eax.h"
#include "..\cryptopp565\gcm.h"

void encryptFile(std::string filename);
void decryptFile(std::string filename);
void findFiles(std::string const &folderName, std::string const &fileMask, char *task);
void generateFileKey(std::string filePath);
void encryptKey(std::string filePath, CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv);
void decryptKey(std::string filePath, CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv);
std::wstring stringToLPCWSTR(const std::string &string);
std::string win32_find_dataToString(const WIN32_FIND_DATA cFile);
CryptoPP::SecByteBlock stringToSecByteBlockKey(const std::string& keyString);
CryptoPP::SecByteBlock stringToSecByteBlockIV(const std::string& ivString);