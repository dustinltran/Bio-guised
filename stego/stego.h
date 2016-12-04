#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>

#include "stego.cpp"


void obfuscate(std::string source, std::string destination);
void removeSubstrs(std::string& s, std::string& p);
void deobfuscate(std::string source, std::string destination);