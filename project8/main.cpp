#include <filesystem>
#include <iostream>
#include <vector>

#include "code_writer.h"
#include "parser.h"

std::vector<std::string> get_files(const std::string& path)
{
	if (path.find(".vm") != std::string::npos)
	{
		return { path };
	}

	std::vector<std::string> files;
	const std::filesystem::path directory{path};
	for (const auto& dir_entry : std::filesystem::recursive_directory_iterator{directory})
	{
		const std::string new_path = dir_entry.path();
		if (new_path.find(".vm", new_path.size() - 3) != std::string::npos)
		{
			files.emplace_back(dir_entry.path());
		}
	}
	return files;
}

int main(int argc, char** argv)
{
	// TODO: Allow taking in a directory and doing all the shits with n Parsers and 1 CodeWriter
	if (argc != 2)
	{
		std::cerr << "Usage: vm_translator <file with .vm extension or directory with .vm files\n";
		return 1;
	}

	std::vector<std::string> files = get_files(argv[1]);

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

