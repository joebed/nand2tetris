#include <algorithm>
#include <sstream>

#include "parser.h"

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

CommandType Parser::command_type(const std::string& line)
{
	std::stringstream ss(line);
	ss << command_str;
	return types::str_to_command_type(command_str);
}

std::string Parser::arg1(const std::string& line, const CommandType command)
{
	std::string trash;
	if (command == CommandType::C_ARITHMETIC)
	{
		ss << arg1;
	}
	else
	{
		ss << trash << arg1;
	}
	return arg1;
}

int Parser::arg2(const std::string& line, const CommandType command)
{
	std::stringstream ss(line);
	std::string trash;
	ss << trash << trash << arg2;
	return arg2;
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
		arg1 = command_str
	}

	return {command_type, arg1, arg2_optional};
}

