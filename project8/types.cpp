#include "types.h"
#include <set>
#include <map>
#include <stdexcept>
#include <unordered_map>

namespace types
{

namespace
{
const std::unordered_map<std::string, CommandType> str_to_command = {
	{"add", ADD},
	{"sub", SUB},
	{"neg", NEG},
	{"eq", EQ},
	{"gt", GT},
	{"lt", LT},
	{"and", AND},
	{"or", OR},
	{"not", NOT},
	{"push", PUSH},
	{"pop", POP},
	{"label", LABEL},
	{"goto", GOTO},
	{"if", IF},
	{"function", FUNCTION},
	{"return", RETURN},
	{"call", CALL},
};

const std::set<CommandType> alu_commands_with_two_operands = {
	ADD,
	SUB,
	EQ,
	GT,
	LT,
	AND,
	OR
};

const std::set<CommandType> alu_commands_with_one_operand = {
	NEG,
	NOT
};

// NOTE: pointer segment is handled by str_to_segment_type function
const std::unordered_map<std::string, SegmentType> str_to_segment = {
	{"local", LOCAL},
	{"argument", ARGUMENT},
	{"this", THIS},
	{"that", THAT},
	{"temp", TEMP},
	{"constant", CONSTANT},
	{"static", STATIC},
};

const std::map<SegmentType, std::string> segment_to_reg_name_map = {
	{CONSTANT, "SP"},
	{LOCAL, "LCL"},
	{ARGUMENT, "ARG"},
	{THIS, "THIS"},
	{THAT, "THAT"},
};

const std::map<CommandType, char> command_to_character_operand_map = {
	{ADD, '+'},
	{SUB, '-'},
	{AND, '&'},
	{OR, '|'},
	{NEG, '-'},
	{NOT, '!'},
};

const std::map<CommandType, std::string> comp_command_to_hack_map = {
	{EQ, "JEQ"},
	{GT, "JGT"},
	{LT, "JLT"},
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
		return (index == 0) ? POINTER_THIS : POINTER_THAT;
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
		std::string s = "unknown segment: " + std::to_string(segment);
		throw std::runtime_error(s);
	}
	return it->second;
}

AluCommandType command_to_operand_type(const CommandType command_type)
{
	auto it = alu_commands_with_two_operands.find(command_type);
	if (it != alu_commands_with_two_operands.end()) return AluCommandType::TwoOperand;
	it = alu_commands_with_one_operand.find(command_type);
	if (it != alu_commands_with_one_operand.end()) return AluCommandType::OneOperand;
	throw std::runtime_error("Tried to call command_to_operand_type on invalid command type");
}

char command_to_character_operand(const CommandType command_type)
{
	auto it = command_to_character_operand_map.find(command_type);
	if (it == command_to_character_operand_map.end())
	{
		std::string s = "Command " + std::to_string(command_type) + " does not have operand in hack assembly";
		throw std::runtime_error(s);
	}
	return it->second;
}

std::string comp_command_to_hack_str(const CommandType command_type)
{
	auto it = comp_command_to_hack_map.find(command_type);
	if (it == comp_command_to_hack_map.end())
	{
		std::string s = "Command " + std::to_string(command_type) + " does not have operand in hack assembly";
		throw std::runtime_error(s);
	}
	return it->second;
}

} // namespace types

