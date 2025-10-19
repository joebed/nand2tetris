#pragma once

#include <fstream>
#include <optional>
#include <set>
#include <string>

#include "types.h"
using namespace types;

class Parser
{
public:
	Parser(const std::string& input_filename);
	std::optional<std::string> advance();
	static std::tuple<CommandType, std::optional<SegmentType>, std::optional<int>> parse_command(const std::string& line);
private:
	std::ifstream fin_;

	static std::set<CommandType> commands_with_arg2;
};



