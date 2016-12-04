#include "stego.h"

int main()
{
	obfuscate("files/test_results.enc", "files/test.py");

	deobfuscate("files/test.py", "files/test_res.enc");

	//return 0;
}