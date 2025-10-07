#pragma once

#include <string>

namespace types
{

enum CommandType
{
	C_ARITHMETIC,
	C_PUSH,
	C_POP,
	C_LABEL,
	C_GOTO,
	C_IF,
	C_FUNCTION,
	C_RETURN,
	C_CALL,
};

CommandType str_to_command_type(const std::string& command_str);

enum SegmentType
{
	CONSTANT,
	LOCAL,
	ARGUMENT,
	THIS,
	THAT,
	TEMP,
};

SegmentType str_to_segment_type(const std::string& segment_str);

} // namespace types

