#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <stdio.h>

 int main(){
    //load the ciphertext file and put it into a single string:
    std::ifstream in("test_results.enc");
    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string ciphertext = buffer.str();
    std::cout << ciphertext << std::endl << std::endl;

    //get the length of the ciphertext string
    int cipherlength = ciphertext.length(); 
    int arraylength = cipherlength / 8;
    std::cout << arraylength << std::endl;
    std::cout << cipherlength << std::endl;

    //std::cout << buffer.size() << std::endl;

    //int extras = cipherlength % 8;
    
    //load ciphertext string into array of size 8 substrings
    std::string *cipherarray = new std::string[arraylength];
    int cur = 0;
    if (cipherlength == 0) 
    {
        return 0;
    }
    //std::cout << arraylength << std::endl;
    for (int i = 0; i <= arraylength; i++)
    {
        //std::cout << ciphertext.substr(cur, 8) << "\n" << std::endl;
        /*if (i = arraylength)
            cipherarray[i] = ciphertext.substr(cur, extras); 
        else*/
        cipherarray[i] = ciphertext.substr(cur, 8);

        cur = cur + 8;
    }

    //std::cout << cipherarray->length() << std::endl;
    std::cout << arraylength << std::endl;

    
    //print out array of substrings of ciphertext
    for (int j = 0; j <= arraylength; j++)
    {
        std::cout << j << ":" + cipherarray[j] + "\n";// << std::endl << std::endl;
    }
    

    //create a string to hold obfuscated ciphertext, i.e. steganography
    std::string stegtext = "";
    if (arraylength % 6 != 0)
    {
        for (int i = 0; i < arraylength % 6; i++)
        {
            stegtext += ("var " + cipherarray[i] + " ;\n");
        }
    }
    /*
    for (int i = (arraylength) % 6; i < arraylength; i = i + 6)
    {
        stegtext += ("function " + cipherarray[i] + "(" + cipherarray[i+1] + "){\n    if (" + cipherarray[i+2] + "==" + cipherarray[i+3] + "){\n        " + cipherarray[i+4] + "++;\n    }\n    " + cipherarray[i+5] + "++;\n}\n\n");
    }
    */
    int i = arraylength % 6;
    while (i < arraylength)
    {
        stegtext += ("function " + cipherarray[i] + " ( " + cipherarray[i+1] + " ){\n    if ( " + cipherarray[i+2] + " == " + cipherarray[i+3] + " ){\n        " + cipherarray[i+4] + " +=1;\n    }\n    " + cipherarray[i+5] + " +=2;\n}\n\n");
        i = i +6;
    }
    if (i <= arraylength) 
    {
        stegtext += "print " + cipherarray[i] + " ;\n";
        //stegtext += "cipherarray i : " + std::to_string(i);
    }

    std::cout << i << "\n" <<std::endl;

    //print out obfuscated ciphertext
    std::cout << stegtext << std::endl;

    std::cout << i << "\n" <<std::endl;
    std::cout << "cipherarray[" << i << "]: " + cipherarray[i] + "\n" << std::endl;


    //write obfuscated stegtext to file
    std::ofstream out("steg.js");
    out << stegtext;
    out.close();
    return 0;
 }