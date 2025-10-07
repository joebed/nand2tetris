#include "types.h"

#include <stdexcept>
#include <unordered_map>

namespace types
{

std::unordered_map<std::string, CommandType> str_to_command = {
	{"add", C_ARITHMETIC},
	{"sub", C_ARITHMETIC},
	{"push", C_PUSH},
	{"pop", C_POP},
	{"label", C_LABEL},
	{"goto", C_GOTO},
	{"if", C_IF},
	{"function", C_FUNCTION},
	{"return", C_RETURN},
	{"call", C_CALL},
};

CommandType str_to_command_type(const std::string& command_str)
{
	auto it = str_to_command.find(command_str);
	if (it == str_to_command.end())
	{
		std::string s = "unknown command: " + command_str;
		throw std::runtime_error(s);
	}
	return it->second;
}

std::unordered_map<std::string, SegmentType> str_to_segment = {
	{"constant", CONSTANT},
	{"local", LOCAL},
	{"argument", ARGUMENT},
	{"this", THIS},
	{"that", THAT},
	{"temp", TEMP},
};

SegmentType str_to_segment_type(const std::string& segment_str)
{
	auto it = str_to_segment.find(segment_str);
	if (it == str_to_segment.end())
	{
		std::string s = "unknown segment: " + segment_str;
		throw std::runtime_error(s);
	}
	return it->second;
}

} // namespace types

