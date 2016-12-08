#include "stdafx.h"

/****************************************************************************************
TASK:   Hide data in a basic python looking file
PRE :   source - file to be hidden
POST:   data from source is hidden in a python looking file
****************************************************************************************/
void obfuscate(std::string source)
{
    std::string destination = source + ".stego";
    std::string ciphertext;

    //load the ciphertext file and put it into a single string:
    std::ifstream in(source, std::ios::binary);
    
    std::stringstream buffer;

    if (!in.is_open()){
        perror("Source file not opened!");
        return;
    }
    buffer << in.rdbuf();
    ciphertext = buffer.str();

    //get the length of the ciphertext string
    int cipherlength = ciphertext.length();
    int arraylength = cipherlength / 8;
    
    std::string *cipherarray = new std::string[arraylength + 1];

    int cur = 0;

    for (int i = 0; i <= arraylength; i++)
    {
        
        cipherarray[i] = ciphertext.substr(cur, 8);
        cur = cur + 8;
    }

    //create a string to hold obfuscated ciphertext, i.e. steganography
    std::string stegtext = "";
    if (arraylength % 6 != 0)
    {
        for (int i = 0; i < arraylength % 6; i++)
        {
            stegtext += ("\n complex " + cipherarray[i]);// + "\n");
        }
    }
    int i = arraylength % 6;
    while (i < arraylength)
    {
        stegtext += ("\n\ndef " + cipherarray[i] + "  ( ( " + cipherarray[i + 1] + " ) ):\n    if ( " + cipherarray[i + 2] + /*" == "*/".compare( " + cipherarray[i + 3] + " ) )\n        " + cipherarray[i + 4] + " +=1\n    " + cipherarray[i + 5] + " +=2\n\n");
        i = i + 6;
    }
    if (i <= arraylength)
    {
        stegtext += "\nprint " + cipherarray[i];
    }

    //write obfuscated stegtext to file
    
    std::ofstream out(destination, std::ios::binary);
    out << stegtext;
    out.close();
    in.close();


    if (_unlink(source.c_str()) == -1)
    {
        std::perror("Could not delete original file unlink");
    }
}

/****************************************************************************************
TASK:   Remove all instances of a pattern from string
PRE :   string - target string
        pattern - pattern to remove from string
POST:   all instances of pattern are removed from string
CITATION: Following function was adapted from
http://stackoverflow.com/questions/32435003/how-to-remove-all-substrings-from-a-string
By Deadlock
****************************************************************************************/
void removeSubstrs(std::string& string, std::string& pattern)
{
    std::string::size_type pEnd = pattern.length();
    for (std::string::size_type i = string.find(pattern);
        i != std::string::npos;
        i = string.find(pattern))
        string.erase(i, pEnd);
}

/****************************************************************************************
TASK:   Unhide data from python looking file
PRE :   source - hidden data to be unhidden
POST:   source data is retrived from hidden file
****************************************************************************************/
void deobfuscate(std::string source)
{
    std::string destination = source.substr(0, source.find(".stego"));
    std::string stegtxt;
    //load the obfuscated text file and put it into a single string
    std::ifstream in(source, std::ios::binary);
    std::stringstream buffer;
    buffer << in.rdbuf();
    stegtxt = buffer.str();
    
    //std::cout << stegtxt << std::endl << std::endl;
    //CryptoPP::FileSource fs(source.c_str(), true, new CryptoPP::StringSink(stegtxt));
    int steglength = stegtxt.length();

    //create string to hold de-steg'd ciphertext (ie regular ciphertext)
    std::string ciphertxt = stegtxt;

    std::string s1 = "\n complex ";
    std::string s2 = "\n\ndef ";
    std::string s3 = " ) ):\n    if ( ";
    std::string s4 = "  ( ( ";
    std::string s5 = ".compare( ";
    std::string s6 = " ) )\n        ";
    std::string s7 = " +=1\n    ";
    std::string s8 = " +=2\n\n";
    std::string s9 = "\nprint ";

    removeSubstrs(ciphertxt, s1);
    removeSubstrs(ciphertxt, s2);
    removeSubstrs(ciphertxt, s3);
    removeSubstrs(ciphertxt, s4);
    removeSubstrs(ciphertxt, s5);
    removeSubstrs(ciphertxt, s6);
    removeSubstrs(ciphertxt, s7);
    removeSubstrs(ciphertxt, s8);
    removeSubstrs(ciphertxt, s9);

    //write de-steg'd ciphertext (ie regulr ciphertext) to file
    //std::cout << ciphertxt << std::endl;
    std::ofstream out(destination, std::ios::binary);

    out << ciphertxt;
    out.close();
    in.close();

    if (_unlink(source.c_str()) == -1)
    {
        std::perror("Could not delete original file unlink");
    }
}