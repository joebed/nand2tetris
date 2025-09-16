#include <algorithm>
#include <sstream>

#include "parser.h"

std::set<CommandType> Parser::commands_with_arg2 = {
	CommandType::C_POP,
	CommandType::C_PUSH,
	CommandType::C_FUNCTION,
	CommandType::C_CALL,
};

Parser::Parser(const std::string& input_filename)
	: fin_(input_filename)
{}

std::optional<std::string> Parser::advance() // copied from Assembler, can refactor into a base class but I don't care to right now
{
	std::string s;
	if (!std::getline(fin_, s))
	{
		return std::nullopt;
	}
	else
	{
		s = s.substr(0, s.find("//"));
		s.erase(std::remove_if(s.begin()
					, s.end()
					, [](unsigned char c) { return std::isspace(c); })
				, s.end());
	}
	
	return (s.size() != 0) // if s.size() == 0, then line is empty or comment only
		? s
		: advance();
}

std::tuple<CommandType, std::string, std::optional<int>> Parser::parse_command(const std::string& line)
{
	std::string command_str;
	std::string arg1;
	int arg2;

	std::optional<int> arg2_optional;

	std::stringstream ss(line);
	ss << command_str;

	const CommandType command_type = str_to_command_type(command_str);
	if (command_type == CommandType::C_ARITHMETIC)
	{
		arg1 = command_str;
	}
	else
	{
		ss << arg1;
	}
	if (commands_with_arg2.find(command_type) != commands_with_arg2.end())
	{
		ss << arg2;
		arg2_optional = arg2;
	}

	return {command_type, arg1, arg2_optional};
}

