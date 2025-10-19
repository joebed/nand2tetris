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

std::string get_output_filename(const std::vector<std::string>& files)
{
	if (files.size() == 1)
	{
		std::string file = files.front();
		file = file.substr(0, file.find(".vm"));
		return file + ".asm";
	}
	std::string s = files.front();
	s = s.substr(0, s.find('/'));
	s = s + "/" + s + ".asm";
	return s;
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: vm_translator <file with .vm extension or directory with .vm files\n";
		return 1;
	}

	std::vector<std::string> files = get_files(argv[1]);
	vm_translator::CodeWriter code_writer;
	std::string s = get_output_filename(files);
	code_writer.set_output_stream(s, files.size() == 1);

	for (const std::string& file : files)
	{
		Parser parser(file);
		std::optional<std::string> s;
		while ((s = parser.advance()))
		{
			code_writer.write_comment(s.value());
			auto [command_type, arg1_optional, arg2_optional] = Parser::parse_command(s.value());
			code_writer.write_command(command_type, arg1_optional, arg2_optional);
		}
	}
	code_writer.close();
	std::cout << "All done :)\n";
}

