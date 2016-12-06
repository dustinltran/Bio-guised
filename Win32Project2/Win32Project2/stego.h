#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <locale>


void obfuscate(std::string source);
void removeSubstrs(std::string& s, std::string& p);
void deobfuscate(std::string source);