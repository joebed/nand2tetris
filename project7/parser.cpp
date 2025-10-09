#include <iostream>
#include <sstream>

#include "parser.h"

std::set<CommandType> Parser::commands_with_arg2 = {
	CommandType::POP,
	CommandType::PUSH,
	CommandType::FUNCTION,
	CommandType::CALL,
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
	}
	
	return (s.size() != 0) // if s.size() == 0, then line is empty or comment only
		? s
		: advance();
}

std::tuple<CommandType, std::optional<SegmentType>, std::optional<int>> Parser::parse_command(const std::string& line)
{
	std::string command_str;
	std::string arg1;
	int arg2;

	std::optional<SegmentType> arg1_optional;
	std::optional<int> arg2_optional;

	std::stringstream ss(line);
	ss >> command_str;

	const CommandType command_type = str_to_command_type(command_str);
	if (!(command_type == CommandType::ADD || command_type == CommandType::SUB))
	{
		ss >> arg1;
	}
	if (commands_with_arg2.find(command_type) != commands_with_arg2.end())
	{
		ss >> arg2;
		arg1_optional = str_to_segment_type(arg1, arg2);
		arg2_optional = arg2;
	}

	return {command_type, arg1_optional, arg2_optional};
}

