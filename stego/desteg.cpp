#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <stdio.h>

 int main(){
	//load the obfuscated text file and put it into a single string
    std::ifstream in("steg.js");
    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string stegtxt = buffer.str();
    std::cout << stegtxt << std::endl << std::endl;

    //create string to hold de-steg'd ciphertext (ie regular ciphertext)
    std::string ciphertxt = "";

    
    //fill ciphertext string with original ciphertext
    std::istringstream iss(stegtxt);
    std::string word;
    while(iss >> word)
    {
    	if (word != "var" && word != "print" && word != "function" && word != "("  && word != "){"  && word != "if" && word != "==" && word != "++;" && word != "+=1;" && word != "+=2;" && word != "}" && word != ";")
    	{
    		ciphertxt += word;
    	}
    }
    
    /*
    //fill ciphertext string with original ciphertext
    std::istringstream buf(std::string temp);
    for (std::string word; buf >> word; )
    {
    	if (word != "print" && word != "function" && word != "("  && word != "){"  && word != "if" && word != "==" && word != "++;" && word != "}")
    	{
    		ciphertxt += word;
    	}
    }
    */

    //write de-steg'd ciphertext (ie regulr ciphertext) to file
    std::ofstream out("desteg.txt");
    out << ciphertxt;
    out.close();
    return 0;
 }