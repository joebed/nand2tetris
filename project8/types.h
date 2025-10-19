#pragma once

#include <optional>
#include <string>

namespace types
{

enum CommandType
{
	ADD,
	SUB,
	NEG,
	EQ,
	GT,
	LT,
	AND,
	OR,
	NOT,
	PUSH,
	POP,
	LABEL,
	GOTO,
	IF,
	FUNCTION,
	RETURN,
	CALL,
};

CommandType str_to_command_type(const std::string& command_str);

enum SegmentType
{
	CONSTANT,
	STATIC,
	LOCAL,
	ARGUMENT,
	THIS,
	THAT,
	POINTER_THIS,
	POINTER_THAT,
	TEMP,
};

SegmentType str_to_segment_type(const std::string& segment_str, const int index);
// Assumes temp, static, and pointer segments are handled before hand since they have special register translation logic
std::string segment_to_reg_name(const SegmentType segment);

enum AluCommandType // the plan was to originally use this for templating the code but I was struggling getting it to compile with my makeshift Makefile
{
	TwoOperand,
	OneOperand,
};

AluCommandType command_to_operand_type(const CommandType command_type);
char command_to_character_operand(const CommandType command_type);
std::string comp_command_to_hack_str(const CommandType command_type);

} // namespace types

