#include <algorithm>

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
}

std::string Parser::arg1(const std::string& line, const CommandType command)
{
}

int Parser::arg2(const std::string& line, const CommandType command)
{
}



