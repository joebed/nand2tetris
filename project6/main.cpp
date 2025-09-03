#include <cctype>
#include <iostream>
#include <string>

#include "assembler.h"



int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "usage: hack_assembler <assembly file with .asm extension>\n";
		return 1;
	}
	
	std::string input_filename = argv[1];
	Assembler assembler(input_filename);
	assembler.assemble();
	return 0;
}

