#include "types.h"

#include <unordered_map>

namespace types
{

using types::CommandType;
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

} // namespace types

