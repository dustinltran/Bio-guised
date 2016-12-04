// Win32Project2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include <iostream>
//#include <iomanip>
//#include <cstdio>
//#include <io.h>
//#include <stdio.h>
//#include <Windows.h>
//#include <string>
//#include <queue>
//#include "..\cryptopp565\hex.h"
//#include "..\cryptopp565\base64.h"
//#include "..\cryptopp565\algparam.h"
//#include "..\cryptopp565\modes.h"
//#include "..\cryptopp565\aes.h"
//#include "..\cryptopp565\filters.h"
//#include "..\cryptopp565\files.h"
//#include "..\cryptopp565\secblock.h"
//#include "..\cryptopp565\osrng.h"
//#include "..\cryptopp565\eax.h"


//void encryptFile(std::string filename);
//void decryptFile(std::string filename);
//std::wstring stringToLPCWSTR(const std::string &string);
//std::string win32_find_dataToString(const WIN32_FIND_DATA cFile);
/*
	Converts type string to type wString which can be cast to LPCWSTR
*/
//std::wstring stringToLPCWSTR(const std::string &string)
//{
//	int len;
//	int stringLength = (int)string.length() + 1;
//	len = MultiByteToWideChar(CP_ACP, 0, string.c_str(), stringLength, 0, 0);
//	wchar_t* buf = new wchar_t[len];
//	MultiByteToWideChar(CP_ACP, 0, string.c_str(), stringLength, buf, len);
//	std::wstring result(buf);
//	delete[] buf;
//	return result;
//}
///*
//	Converts a WIN32_FIND_DATA to a string
//*/
//std::string win32_find_dataToString(const WIN32_FIND_DATA cFile){
//	char fNam[260];
//	char dChar = ' ';
//	WideCharToMultiByte(CP_ACP, 0, cFile.cFileName, -1, fNam, 260, &dChar, NULL);
//	std::string sFileName(fNam);
//
//	return sFileName;
//}
//
///*
//	test for find files
//*/
//void process(std::string const &path, WIN32_FIND_DATA const &file) {
//	std::cout << path << win32_find_dataToString(file).c_str() << "\n";
//}
///*
//	Finds files in directory and its subdirectories
//*/
//void findFiles(std::string const &folderName, std::string const &fileMask, char *task){
//	HANDLE fileHandler;
//	WIN32_FIND_DATA currentFile;
//	std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string> > directory;
//
//	directory.push(folderName);
//
//	do
//	{
//		std::string filePath = directory.top();
//		directory.pop();
//
//		if (filePath[filePath.size() - 1] != '\\')
//		{
//			filePath += "\\";
//		}
//
//		std::wstring absolutePathMask = stringToLPCWSTR(filePath + fileMask);
//
//		if (INVALID_HANDLE_VALUE == (fileHandler = FindFirstFile(absolutePathMask.c_str(), &currentFile)))
//		{
//			continue;
//		}
//
//		do
//		{
//			if (!(currentFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
//			{
//				// what to do with file
//				//process(filePath, currentFile); // for testing
//				if (strcmp(task, "e") == 0)
//				{
//					encryptFile(filePath + win32_find_dataToString(currentFile));
//				}
//				else
//				{
//					decryptFile(filePath + win32_find_dataToString(currentFile));
//				}
//				
//			}
//		} while (FindNextFile(fileHandler, &currentFile));
//		FindClose(fileHandler);
//
//		std::wstring fPath = stringToLPCWSTR(filePath + "*");
//
//		if (INVALID_HANDLE_VALUE == (fileHandler = FindFirstFile(fPath.c_str(), &currentFile)))
//		{
//			continue;
//		}
//
//		do
//		{
//			if ((currentFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (currentFile.cFileName[0] != '.'))
//			{
//				std::string currFileName = win32_find_dataToString(currentFile);
//				
//				directory.push(filePath + currFileName);
//			}
//		} while (FindNextFile(fileHandler, &currentFile));
//		FindClose(fileHandler);
//	} while (!directory.empty());
//}
//
//
///*
//	Encrypts files	
//*/
//void encryptFile(std::string filename){
//	std::string ofilename = filename;//"test_results.txt";
//	std::string efilename = filename + ".enc";//"test_results.enc";
//	std::string keyStorage = "key.txt";
//	CryptoPP::Base64Encoder encoder;
//	CryptoPP::AlgorithmParameters params = CryptoPP::MakeParameters(CryptoPP::Name::Pad(), false)(CryptoPP::Name::InsertLineBreaks(), false);
//	encoder.Initialize(params);
//
//	/* START DECODING */
//	CryptoPP::ByteQueue bQueue;
//	CryptoPP::FileSource fileSource(keyStorage.c_str(), false, new CryptoPP::Base64Decoder(new CryptoPP::Redirector(bQueue)));
//    fileSource.PumpAll();
//
//	// Reading key & iv
//	CryptoPP::SecByteBlock key, iv;
//	CryptoPP::word16 size = 0;
//
//	// Reading key
//	bQueue.GetWord16(size, CryptoPP::BIG_ENDIAN_ORDER);
//	key.resize(size);
//	bQueue.Get(key, key.size());
//	// Reading iv
//	bQueue.GetWord16(size, CryptoPP::BIG_ENDIAN_ORDER);
//	iv.resize(size);
//	bQueue.Get(iv, iv.size());
//
//	/* END DECODING */
//
//	/* START ENCRYPTION */
//	try {
//		CryptoPP::EAX< CryptoPP::AES >::Encryption e1;
//		e1.SetKeyWithIV(key, key.size(), iv, iv.size());
//
//		CryptoPP::FileSource fs1(ofilename.c_str(), true,
//			new CryptoPP::AuthenticatedEncryptionFilter(e1,
//			new CryptoPP::FileSink(efilename.c_str())));
//
//		//std::cout << "File Encrypted as:" << efilename << std::endl;
//	}
//	catch (CryptoPP::Exception const& ex) {
//		std::cout << ex.what() << std::endl;
//	}
//	/* END ENCRYPTION */
//	if (_unlink(ofilename.c_str()) == -1)
//	{
//		std::perror("Could not delete original file unlink");
//	}
//	else
//	{
//		/*if (std::remove(ofilename.c_str()) != 0)
//		{
//			std::perror("Could not delete original file remove");
//		}
//		else
//		{
//			std::wstring tempString = stringToLPCWSTR(ofilename);
//			LPCWSTR lofilename = tempString.c_str();
//			if (DeleteFile(lofilename) == 0)
//			{
//				printf("getting last error");
//				GetLastError();
//			}
//			else
//			{
//				std::printf("Original file deleted");
//			}
//			std::printf("Original file deleted");
//		}*/
//		//std::cout << "Original file deleted" << std::endl;
//	}
//	/* START ENCODING */
//
//	// Writing the key
//	encoder.PutWord16(static_cast<CryptoPP::word16>(key.size()), CryptoPP::BIG_ENDIAN_ORDER);
//	encoder.Put(key.data(), key.size());
//
//	// Writing the iv
//	encoder.PutWord16(static_cast<CryptoPP::word16>(iv.size()), CryptoPP::BIG_ENDIAN_ORDER);
//	encoder.Put(iv.data(), iv.size());
//	encoder.MessageEnd();
//
//	// Save it to file
//	CryptoPP::FileSink fileSink(keyStorage.c_str(), true);
//    encoder.CopyTo(fileSink);
//    fileSink.MessageEnd();
//	/* END ENCODING */
//}
///*
//	Decrypts files
//*/
//void decryptFile(std::string filename){
//	std::string efilename = filename;//"test_results.txt.enc";
//	std::string rfilename = filename.substr(0, filename.find(".enc"));//"test_results_recovered.txt";
//	std::string keyStorage = "key.txt";
//	CryptoPP::Base64Encoder encoder;
//	CryptoPP::AlgorithmParameters params = CryptoPP::MakeParameters(CryptoPP::Name::Pad(),
//		false)(CryptoPP::Name::InsertLineBreaks(), false);
//	encoder.Initialize(params);
//
//	/* START DECODING */
//	CryptoPP::ByteQueue bQueue;
//	CryptoPP::FileSource fileSource(keyStorage.c_str(), false,
//		new CryptoPP::Base64Decoder(new CryptoPP::Redirector(bQueue)));
//    fileSource.PumpAll();
//
//	// Reading key & iv
//	CryptoPP::SecByteBlock key, iv, key2, iv2;
//	CryptoPP::word16 size = 0;
//
//	// Reading key
//	bQueue.GetWord16(size, CryptoPP::BIG_ENDIAN_ORDER);
//	key.resize(size);
//	bQueue.Get(key, key.size());
//
//	// Reading iv
//	bQueue.GetWord16(size, CryptoPP::BIG_ENDIAN_ORDER);
//	iv.resize(size);
//	bQueue.Get(iv, iv.size());
//
//	/* END DECODING */
//
//	/* START DECRYPTION */
//	try {
//		CryptoPP::EAX< CryptoPP::AES >::Decryption d2;
//		d2.SetKeyWithIV(key, key.size(), iv, iv.size());
//
//		CryptoPP::FileSource fs2(efilename.c_str(), true,
//			new CryptoPP::AuthenticatedDecryptionFilter(d2,
//			new CryptoPP::FileSink(rfilename.c_str()),
//			CryptoPP::AuthenticatedDecryptionFilter::THROW_EXCEPTION
//			));
//		
//
//		//std::cout << "File Decrypted as:" << rfilename << std::endl;
//	}
//	catch (CryptoPP::Exception const& ex) {
//		std::cout << ex.what() << std::endl;
//	}
//	/* END DECRYPTION */
//
//	if (_unlink(efilename.c_str()) == -1)
//	{
//		std::perror("Could not delete original file unlink");
//	}
//	else
//	{
//		/*if (std::remove(ofilename.c_str()) != 0)
//		{
//		std::perror("Could not delete original file remove");
//		}
//		else
//		{
//		std::wstring tempString = stringToLPCWSTR(ofilename);
//		LPCWSTR lofilename = tempString.c_str();
//		if (DeleteFile(lofilename) == 0)
//		{
//		printf("getting last error");
//		GetLastError();
//		}
//		else
//		{
//		std::printf("Original file deleted");
//		}
//		std::printf("Original file deleted");
//		}*/
//		//std::cout << "Original file deleted" << std::endl;
//	}
//
//	/* START ENCODING */
//
//	// Writing the key
//	encoder.PutWord16(static_cast<CryptoPP::word16>(key.size()), CryptoPP::BIG_ENDIAN_ORDER);
//	encoder.Put(key.data(), key.size());
//
//	// Writing the iv
//	encoder.PutWord16(static_cast<CryptoPP::word16>(iv.size()), CryptoPP::BIG_ENDIAN_ORDER);
//	encoder.Put(iv.data(), iv.size());
//	encoder.MessageEnd();
//
//	// Save it to file
//	CryptoPP::FileSink fileSink(keyStorage.c_str(), true);
//    encoder.CopyTo(fileSink);
//    fileSink.MessageEnd();
//	/* END ENCODING */
//}
///*
//	Generates key for encyption and stores it.
//*/
//void generateFileKey(std::string filePath){
//	std::string keyStorage = filePath + "\\key.txt";
//
//	CryptoPP::Base64Encoder encoder;
//	CryptoPP::AlgorithmParameters params = CryptoPP::MakeParameters(CryptoPP::Name::Pad(), false)(CryptoPP::Name::InsertLineBreaks(), false);
//	encoder.Initialize(params);
//
//	// Generate random key and iv
//	CryptoPP::AutoSeededRandomPool prng;
//	CryptoPP::SecByteBlock key(CryptoPP::AES::MAX_KEYLENGTH);
//	prng.GenerateBlock(key, key.size());
//
//	CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
//	prng.GenerateBlock(iv, iv.size());
//
//	// Writing the key
//	encoder.PutWord16(static_cast<CryptoPP::word16>(key.size()), CryptoPP::BIG_ENDIAN_ORDER);
//	encoder.Put(key.data(), key.size());
//
//	// Writing the iv
//	encoder.PutWord16(static_cast<CryptoPP::word16>(iv.size()), CryptoPP::BIG_ENDIAN_ORDER);
//	encoder.Put(iv.data(), iv.size());
//	encoder.MessageEnd();
//
//	// Save it to file
//	CryptoPP::FileSink fileSink(keyStorage.c_str(), true);
//    encoder.CopyTo(fileSink);
//    fileSink.MessageEnd();
//}
///*
//	Encrypts key for file encryption after scanner disconnection.
//*/
//void encryptKey(std::string filePath, CryptoPP::SecByteBlock key){
//	
//}
///*
//	Decrypts key for file encryption/decryption after scaner authentication.
//*/
//void decryptKey(std::string filePath, CryptoPP::SecByteBlock key){
//
//}

int main(int argc, char **argv)
{
	char choice = NULL;
	std::string filePath = "";
    std::string key = "";
	//std::cout << "Path:	" << argv[2] << std::endl;
	//std::cout << argc << std::endl;
	if (argc == 3)
	{
		choice = *argv[1];
		filePath = argv[2];
	}
	else
	{
        if (argc == 4)
        {
            choice = *argv[1];
            filePath = argv[2];
            key = argv[3];
        }
        else
        {
            std::perror("Invalid file path");
            return 0;
        }	
	}
	//std::cout << argc << std::endl;
	
	switch (choice)
	{
		case 'e':
		{
			// Encrypt
			//findFiles("G:\\testfolder\\", "*", "e");
			findFiles(filePath, "*", "e");
		}
		break;
		case 'd':
		{
			// Decrypt
			//findFiles("G:\\testfolder\\", "*", "d");
			findFiles(filePath, "*", "d");
		}
		break;
		case 'k':
		{
			// Generate Key
			// TODO: Update to pass in filePath to make sure key is stored in proper location
			generateFileKey(filePath);
		}
		break;
		case 'x':
		{
			//TODO: Create Encryption for Key
            encryptKey(filePath, stringToSecByteBlockKey(key), stringToSecByteBlockIV(key));
		}
        break;
		case 'y':
		{
			//TODO: Create Decryption for key
            decryptKey(filePath, stringToSecByteBlockKey(key), stringToSecByteBlockIV(key));
		}
		break;
		default:
			break;
	}

	//system("pause");
	return 0;
}

