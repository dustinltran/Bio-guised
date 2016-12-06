// stdafx.cpp : source file that includes just the standard includes
// Win32Project2.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
std::wstring stringToLPCWSTR(const std::string &string)
{
    int len;
    int stringLength = (int)string.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, string.c_str(), stringLength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, string.c_str(), stringLength, buf, len);
    std::wstring result(buf);
    delete[] buf;
    return result;
}
/*
Converts a WIN32_FIND_DATA to a string
*/
std::string win32_find_dataToString(const WIN32_FIND_DATA cFile){
    char fNam[260];
    char dChar = ' ';
    WideCharToMultiByte(CP_ACP, 0, cFile.cFileName, -1, fNam, 260, &dChar, NULL);
    std::string sFileName(fNam);

    return sFileName;
}

/*
Finds files in directory and its subdirectories
*/
void findFiles(std::string const &folderName, std::string const &fileMask, char *task){
    HANDLE fileHandler;
    WIN32_FIND_DATA currentFile;
    std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string> > directory;

    directory.push(folderName);

    do
    {
        std::string filePath = directory.top();
        directory.pop();

        if (filePath[filePath.size() - 1] != '\\')
        {
            filePath += "\\";
        }

        std::wstring absolutePathMask = stringToLPCWSTR(filePath + fileMask);

        if (INVALID_HANDLE_VALUE == (fileHandler = FindFirstFile(absolutePathMask.c_str(), &currentFile)))
        {
            continue;
        }

        do
        {
            if (!(currentFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
            {
                // what to do with file
                std::string source = filePath + win32_find_dataToString(currentFile);
                std::string deskini = filePath + "desktop.ini";
                if (strcmp(source.c_str(), deskini.c_str()) != 0){
                    if (strcmp(task, "e") == 0)
                    {
                        encryptFile(filePath + win32_find_dataToString(currentFile));
                    }
                    else if (strcmp(task, "d") == 0)
                    {
                        decryptFile(filePath + win32_find_dataToString(currentFile));
                    }
                    else if (strcmp(task, "h") == 0)
                    {
                        obfuscate(filePath + win32_find_dataToString(currentFile));
                    }
                    else
                    {
                        deobfuscate(filePath + win32_find_dataToString(currentFile));
                    }
                }
            }
        } while (FindNextFile(fileHandler, &currentFile));
        FindClose(fileHandler);

        std::wstring fPath = stringToLPCWSTR(filePath + "*");

        if (INVALID_HANDLE_VALUE == (fileHandler = FindFirstFile(fPath.c_str(), &currentFile)))
        {
            continue;
        }

        do
        {
            if ((currentFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && (currentFile.cFileName[0] != '.'))
            {
                std::string currFileName = win32_find_dataToString(currentFile);

                directory.push(filePath + currFileName);
            }
        } while (FindNextFile(fileHandler, &currentFile));
        FindClose(fileHandler);
    } while (!directory.empty());
}


/*
Encrypts files
*/
void encryptFile(std::string filename){
    std::string ofilename = filename;//"test_results.txt";
    std::string efilename = filename + ".enc";//"test_results.txt.enc";
    std::string keyStorage = "key.txt";
    CryptoPP::Base64Encoder encoder;
    CryptoPP::AlgorithmParameters params = CryptoPP::MakeParameters(CryptoPP::Name::Pad(), false)(CryptoPP::Name::InsertLineBreaks(), false);
    encoder.Initialize(params);

    /* START DECODING */
    CryptoPP::ByteQueue bQueue;
    CryptoPP::FileSource fileSource(keyStorage.c_str(), false, new CryptoPP::Base64Decoder(new CryptoPP::Redirector(bQueue)));
    fileSource.PumpAll();

    // Reading key & iv
    CryptoPP::SecByteBlock key, iv;
    CryptoPP::word16 size = 0;

    // Reading key
    bQueue.GetWord16(size, CryptoPP::BIG_ENDIAN_ORDER);
    key.resize(size);
    bQueue.Get(key, key.size());
    // Reading iv
    bQueue.GetWord16(size, CryptoPP::BIG_ENDIAN_ORDER);
    iv.resize(size);
    bQueue.Get(iv, iv.size());

    /* END DECODING */

    /* START ENCRYPTION */
    try {
        CryptoPP::EAX< CryptoPP::AES >::Encryption e1;
        e1.SetKeyWithIV(key, key.size(), iv, iv.size());

        CryptoPP::FileSource fs1(ofilename.c_str(), true,
            new CryptoPP::AuthenticatedEncryptionFilter(e1,
            new CryptoPP::FileSink(efilename.c_str())));
    }
    catch (CryptoPP::Exception const& ex) {
        std::cout << ex.what() << std::endl;
    }
    /* END ENCRYPTION */
    if (_unlink(ofilename.c_str()) == -1)
    {
        std::perror("Could not delete original file unlink");
    }
    else
    {
        /*if (std::remove(ofilename.c_str()) != 0)
        {
        std::perror("Could not delete original file remove");
        }
        else
        {
        std::wstring tempString = stringToLPCWSTR(ofilename);
        LPCWSTR lofilename = tempString.c_str();
        if (DeleteFile(lofilename) == 0)
        {
        printf("getting last error");
        GetLastError();
        }
        else
        {
        std::printf("Original file deleted");
        }
        std::printf("Original file deleted");
        }*/
        //std::cout << "Original file deleted" << std::endl;
    }
    /* START ENCODING */

    // Writing the key
    encoder.PutWord16(static_cast<CryptoPP::word16>(key.size()), CryptoPP::BIG_ENDIAN_ORDER);
    encoder.Put(key.data(), key.size());

    // Writing the iv
    encoder.PutWord16(static_cast<CryptoPP::word16>(iv.size()), CryptoPP::BIG_ENDIAN_ORDER);
    encoder.Put(iv.data(), iv.size());
    encoder.MessageEnd();

    // Save it to file
    CryptoPP::FileSink fileSink(keyStorage.c_str(), true);
    encoder.CopyTo(fileSink);
    fileSink.MessageEnd();
    /* END ENCODING */
    //return;
}
/*
Decrypts files
*/
void decryptFile(std::string filename){
    std::string efilename = filename;//"test_results.txt.enc";
    std::string rfilename = filename.substr(0, filename.find(".enc"));//"test_results_recovered.txt";
    std::string keyStorage = "key.txt";
    CryptoPP::Base64Encoder encoder;
    CryptoPP::AlgorithmParameters params = CryptoPP::MakeParameters(CryptoPP::Name::Pad(),
        false)(CryptoPP::Name::InsertLineBreaks(), false);
    encoder.Initialize(params);

    /* START DECODING */
    CryptoPP::ByteQueue bQueue;
    CryptoPP::FileSource fileSource(keyStorage.c_str(), false,
        new CryptoPP::Base64Decoder(new CryptoPP::Redirector(bQueue)));
    fileSource.PumpAll();

    // Reading key & iv
    CryptoPP::SecByteBlock key, iv, key2, iv2;
    CryptoPP::word16 size = 0;

    // Reading key
    bQueue.GetWord16(size, CryptoPP::BIG_ENDIAN_ORDER);
    key.resize(size);
    bQueue.Get(key, key.size());

    // Reading iv
    bQueue.GetWord16(size, CryptoPP::BIG_ENDIAN_ORDER);
    iv.resize(size);
    bQueue.Get(iv, iv.size());

    /* END DECODING */

    /* START DECRYPTION */
    try {
        CryptoPP::EAX< CryptoPP::AES >::Decryption d2;
        d2.SetKeyWithIV(key, key.size(), iv, iv.size());

        CryptoPP::FileSource fs2(efilename.c_str(), true,
            new CryptoPP::AuthenticatedDecryptionFilter(d2,
            new CryptoPP::FileSink(rfilename.c_str()),
            CryptoPP::AuthenticatedDecryptionFilter::THROW_EXCEPTION
            ));
    }
    catch (CryptoPP::Exception const& ex) {
        std::cout << ex.what() << std::endl;
    }
    /* END DECRYPTION */

    if (_unlink(efilename.c_str()) == -1)
    {
        std::perror("Could not delete original file unlink");
    }
    else
    {
        /*if (std::remove(ofilename.c_str()) != 0)
        {
        std::perror("Could not delete original file remove");
        }
        else
        {
        std::wstring tempString = stringToLPCWSTR(ofilename);
        LPCWSTR lofilename = tempString.c_str();
        if (DeleteFile(lofilename) == 0)
        {
        printf("getting last error");
        GetLastError();
        }
        else
        {
        std::printf("Original file deleted");
        }
        std::printf("Original file deleted");
        }*/
        //std::cout << "Original file deleted" << std::endl;
    }

    /* START ENCODING */

    // Writing the key
    encoder.PutWord16(static_cast<CryptoPP::word16>(key.size()), CryptoPP::BIG_ENDIAN_ORDER);
    encoder.Put(key.data(), key.size());

    // Writing the iv
    encoder.PutWord16(static_cast<CryptoPP::word16>(iv.size()), CryptoPP::BIG_ENDIAN_ORDER);
    encoder.Put(iv.data(), iv.size());
    encoder.MessageEnd();

    // Save it to file
    CryptoPP::FileSink fileSink(keyStorage.c_str(), true);
    encoder.CopyTo(fileSink);
    fileSink.MessageEnd();
    /* END ENCODING */
}
/*
Generates key for encyption and stores it.
*/
void generateFileKey(std::string filePath){
    std::string keyStorage = filePath + "\\key.txt";

    CryptoPP::Base64Encoder encoder;
    CryptoPP::AlgorithmParameters params = CryptoPP::MakeParameters(CryptoPP::Name::Pad(), false)(CryptoPP::Name::InsertLineBreaks(), false);
    encoder.Initialize(params);

    // Generate random key and iv
    CryptoPP::AutoSeededRandomPool prng;
    CryptoPP::SecByteBlock key(CryptoPP::AES::MAX_KEYLENGTH);
    prng.GenerateBlock(key, key.size());

    CryptoPP::SecByteBlock iv(CryptoPP::AES::BLOCKSIZE);
    prng.GenerateBlock(iv, iv.size());

    // Writing the key
    encoder.PutWord16(static_cast<CryptoPP::word16>(key.size()), CryptoPP::BIG_ENDIAN_ORDER);
    encoder.Put(key.data(), key.size());

    // Writing the iv
    encoder.PutWord16(static_cast<CryptoPP::word16>(iv.size()), CryptoPP::BIG_ENDIAN_ORDER);
    encoder.Put(iv.data(), iv.size());
    encoder.MessageEnd();

    // Save it to file
    CryptoPP::FileSink fileSink(keyStorage.c_str(), true);
    encoder.CopyTo(fileSink);
    fileSink.MessageEnd();
}
/*
Encrypts key for file encryption after scanner disconnection.
*/
void encryptKey(std::string filePath, CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv){
    std::string keyStorage = filePath + "\\key.txt";
    std::string ekeyStorage = filePath + "\\ekey.txt";
    const int TAG_SIZE = 12;

    try
    {
        CryptoPP::GCM<CryptoPP::AES>::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv, iv.size());

        CryptoPP::FileSource fileSource(keyStorage.c_str(), true,
            new CryptoPP::AuthenticatedEncryptionFilter(e,
            new CryptoPP::FileSink(ekeyStorage.c_str()), false, TAG_SIZE));
    }
    catch (CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    if (_unlink(keyStorage.c_str()) == -1)
    {
        std::perror("Could not delete original file unlink");
    }
}
/*
Decrypts key for file encryption/decryption after scaner authentication.
*/
void decryptKey(std::string filePath, CryptoPP::SecByteBlock key, CryptoPP::SecByteBlock iv){
    std::string keyStorage = filePath + "\\ekey.txt";
    std::string dkeyStorage = filePath + "\\key.txt";
    const int TAG_SIZE = 12;

    try
    {
        CryptoPP::GCM<CryptoPP::AES>::Decryption d;
        d.SetKeyWithIV(key, key.size(), iv, iv.size());

        CryptoPP::FileSource fileSource(keyStorage.c_str(), true,
            new CryptoPP::AuthenticatedDecryptionFilter(d,
            new CryptoPP::FileSink(dkeyStorage.c_str()), false, TAG_SIZE));
    }
    catch (CryptoPP::Exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    if (_unlink(keyStorage.c_str()) == -1)
    {
        std::perror("Could not delete original file unlink");
    }
}

CryptoPP::SecByteBlock stringToSecByteBlockKey(const std::string& keyString){
    CryptoPP::SecByteBlock key((const byte*)keyString.data(), keyString.size());

    if (key.size() < CryptoPP::AES::MAX_KEYLENGTH)
    {
        key.CleanGrow(CryptoPP::AES::MAX_KEYLENGTH); // pads with 0 to reach appropriate size
    }
    else
    {
        key.resize(CryptoPP::AES::MAX_KEYLENGTH); // truncate if too large
    }

    //std::cout << "Derived key: ";
    //CryptoPP::ArraySource(key.data(), key.size(), true, new CryptoPP::HexEncoder(new CryptoPP::FileSink(std::cout)));
    //std::cout << std::endl;
    return key;
}

CryptoPP::SecByteBlock stringToSecByteBlockIV(const std::string& ivString){
    CryptoPP::SecByteBlock iv((const byte*)ivString.data(), ivString.size());

    if (iv.size() < CryptoPP::AES::BLOCKSIZE)
    {
        iv.CleanGrow(CryptoPP::AES::BLOCKSIZE); // pads with 0 to reach appropriate size
    }
    else
    {
        iv.resize(CryptoPP::AES::BLOCKSIZE); // truncate if too large
    }

    //std::cout << "Derived key: ";
    //CryptoPP::ArraySource(iv.data(), iv.size(), true, new CryptoPP::HexEncoder(new CryptoPP::FileSink(std::cout)));
    //std::cout << std::endl;
    return iv;
}
