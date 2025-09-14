#include <fstream>
#include <iostream>

#include "code_writer.h"
#include "parser.h"

int main(int argc, char** argv)
{
	// TODO: Allow taking in a directory and doing all the shits with n Parsers and 1 CodeWriter
	if (argc != 2)
	{
		std::cerr << "Usage: vm_translator <file with .vm extension>\n";
		return 1;
	}

	std::vector<std::string> files;
	CodeWriter code_writer;
	for (const std::string& file : files)
	{
		Parser parser(file);
		// output file needed for output stream
		std::string output_filename = "";
		code_writer.set_output_stream(output_filename);
		std::string s;
		while ((s = parser.advance()))
		{
			CommandType command_type = Parser::command_type(s);
			if (command_type == CommandType::C_PUSH || command_type == CommandType::C_POP)
			{
				code_writer(
			}
			else if (command_type = CommandType::C_ARITHMETIC)
			{
				code_writer.write_arithmetic(line);
			}
		}

		
		code_writer.close();
	}


}

