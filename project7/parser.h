#pragma once

#include <fstream>
#include <optional>
#include <string>

#include "types.h"

class Parser
{
public:
	Parser(const std::string& input_filename);
	std::optional<std::string> advance();
	static CommandType command_type(const std::string& line);
	static std::string arg1(const std::string& line, const CommandType command);
	static int arg2(const std::string& line, const CommandType command);
private:
	std::ifstream fin_;
};

