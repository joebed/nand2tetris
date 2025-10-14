#include <iostream>
#include <vector>

#include "code_writer.h"
#include "parser.h"

int main(int argc, char** argv)
{
	// TODO: Allow taking in a directory and doing all the shits with n Parsers and 1 CodeWriter
	if (argc == 1)
	{
		std::cerr << "Usage: vm_translator <file with .vm extension>\n";
		return 1;
	}

	std::vector<std::string> files;
	for (int i = 1; i < argc; ++i)
	{
		files.push_back(argv[i]);
	}

	vm_translator::CodeWriter code_writer;
	for (const std::string& file : files)
	{
		Parser parser(file);
		code_writer.set_output_stream(file);
		std::optional<std::string> s;
		while ((s = parser.advance()))
		{
			code_writer.write_comment(s.value());
			std::cout << "Working on " << s.value() << "\n";
			auto [command_type, arg1_optional, arg2_optional] = Parser::parse_command(s.value());
			code_writer.write_command(command_type, arg1_optional, arg2_optional);
		}
		code_writer.close();
	}
	std::cout << "All done :)\n";
}

