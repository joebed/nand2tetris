#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

#include "parser.h"

std::string get_output_file(const std::string& input_filename)
{
	size_t ext = input_filename.find(".asm");
	if (ext == std::string::npos)
	{
		std::cerr << "usage: hack_assembler <assembly file with .asm extension>\n";
		throw std::runtime_error("bruh");
	}
	return input_filename.substr(0, ext) + ".hack";
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "usage: hack_assembler <assembly file with .asm extension>\n";
		return 1;
	}
	
	std::string input_filename = argv[1];
	std::string output_filename = get_output_file(input_filename);
	std::ofstream fout(output_filename);

		

		// std::cout << "working on '" << s << "'\t\t";
		// Instruction ins;
		// bool is_a_instruction = s.front() == '@';
		// ins = (is_a_instruction)
		// 	? process_a_instruction(s)
		// 	: process_c_instruction(s);
		//
		// std::cout << ((is_a_instruction) ? ins.to_ulong() : ins) << "\n";
		//
		// fout << ins << "\n";
	

	std::cout << "Success! Output written to " << output_filename << "\n";
	return 0;
}

