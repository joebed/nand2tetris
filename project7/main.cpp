#include <fstream>
#include <iostream>
#include <vector>

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
	{;
		Parser parser(file);
		// output file needed for output stream
		std::string output_filename = "";
		code_writer.set_output_stream(output_filename);
		std::optional<std::string> s;
		while ((s = parser.advance()))
		{
			auto [command_type, arg1, arg2_optional] = Parser::parse_command(s.value());
			if (command_type == CommandType::C_PUSH || command_type == CommandType::C_POP)
			{
				code_writer.write_push_pop(command_type, arg1, arg2_optional.value());
			}
			else if (command_type == CommandType::C_ARITHMETIC)
			{
				code_writer.write_arithmetic(line);
			}
		}

		
		code_writer.close();
	}
}

