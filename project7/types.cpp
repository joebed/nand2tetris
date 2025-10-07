#include "types.h"

#include <map>
#include <stdexcept>
#include <unordered_map>

namespace types
{

namespace
{
const std::unordered_map<std::string, CommandType> str_to_command = {
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

// NOTE: pointer segment is handled by str_to_segment_type function
const std::unordered_map<std::string, SegmentType> str_to_segment = {
	{"constant", CONSTANT},
	{"static", STATIC},
	{"local", LOCAL},
	{"argument", ARGUMENT},
	{"temp", TEMP},
};

const std::map<SegmentType, std::string> segment_to_reg_name_map = {
	{CONSTANT, "SP"},
	{STATIC, ""},
	{LOCAL, "LCL"},
	{ARGUMENT, "ARG"},
	{THIS, "THIS"},
	{THAT, "THAT"},
	{TEMP, "R"},
};

} // namespace

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

SegmentType str_to_segment_type(const std::string& segment_str, const int index)
{
	if (segment_str == "pointer")
	{
		return (index == 0) ? THIS : THAT;
	}

	auto it = str_to_segment.find(segment_str);
	if (it == str_to_segment.end())
	{
		std::string s = "unknown segment: " + segment_str;
		throw std::runtime_error(s);
	}
	return it->second;
}

std::string segment_to_reg_name(const SegmentType segment)
{
	auto it = segment_to_reg_name_map.find(segment);
	if (it == segment_to_reg_name_map.end())
	{
		std::string s = "unknown segment: " + segment;
		throw std::runtime_error(s);
	}
	return it->second;
}

} // namespace types

