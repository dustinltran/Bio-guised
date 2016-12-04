

void obfuscate(std::string source, std::string destination)
{
     //load the ciphertext file and put it into a single string:
    std::ifstream in(source);
    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string ciphertext = buffer.str();
    std::cout << ciphertext << std::endl << std::endl;

    //get the length of the ciphertext string
    int cipherlength = ciphertext.length(); 
    int arraylength = cipherlength / 8;
    std::cout << arraylength << std::endl;
    std::cout << cipherlength << std::endl;

    std::string *cipherarray = new std::string[arraylength];

    int cur = 0;
    /*
    if (cipherlength == 0) 
    {
        return 0;
    }
    */


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
        stegtext += ("\n\ndef " + cipherarray[i] + "  ( ( " + cipherarray[i+1] + " ) ):\n    if ( " + cipherarray[i+2] + /*" == "*/".compare( " + cipherarray[i+3] + " ) )\n        " + cipherarray[i+4] + " +=1\n    " + cipherarray[i+5] + " +=2\n\n");
        i = i +6;
    }
    if (i <= arraylength) 
    {
        stegtext += "\nprint " + cipherarray[i];
    }


    //write obfuscated stegtext to file
    std::ofstream out(destination);
    out << stegtext;
    out.close();
    //return 0;

}

void removeSubstrs(std::string& s, std::string& p) 
{ 
  std::string::size_type n = p.length();
  for (std::string::size_type i = s.find(p);
      i != std::string::npos;
      i = s.find(p))
      s.erase(i, n);
}

void deobfuscate(std::string source, std::string destination)
{
	//load the obfuscated text file and put it into a single string
    std::ifstream in(source);
    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string stegtxt = buffer.str();
    std::cout << stegtxt << std::endl << std::endl;

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
    std::ofstream out(destination);
    out << ciphertxt;
    //out << stegtxt.substr(0, 4) + ";";
    out.close();
    //return 0;



}