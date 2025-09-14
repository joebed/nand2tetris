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

} // namespace types

