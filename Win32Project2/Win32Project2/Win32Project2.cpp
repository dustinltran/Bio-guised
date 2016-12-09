// Win32Project2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char **argv)
{
	char choice = NULL;
	std::string filePath = "";
    std::string key = "";

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
	
	switch (choice)
	{
		case 'e':
		{
			// Encrypt
            findFiles(filePath, "*", "e");
            findFiles(filePath, "*", "h");
		}
		break;
		case 'd':
		{
			// Decrypt
            findFiles(filePath, "*", "u");
            findFiles(filePath, "*", "d");
		}
		break;
		case 'k':
		{
			// Generate Key
			generateFileKey(filePath);
		}
		break;
		case 'x':
		{
			//Encryption for Key
            encryptKey(filePath, stringToSecByteBlockKey(key), stringToSecByteBlockIV(key));
		}
        break;
		case 'y':
		{
			//Decryption for key
            decryptKey(filePath, stringToSecByteBlockKey(key), stringToSecByteBlockIV(key));
		}
		break;
		default:
			break;
	}
	return 0;
}
