#include <stdexcept>

#include "code_writer.h"

CodeWriter::CodeWriter(const std::string& output_filename)
	: fout_(output_filename)
{}

void CodeWriter::write_arithmetic(const std::string& command)
{
}

void CodeWriter::write_push_pop(const CommandType command, const std::string& segment, const int index)
{
	if (command == C_PUSH)
	{
	}
	else if (command == C_POP)
	{
	}
	else
	{
		throw std::runtime_error("Called write_push_pop on bad command"); // should never happen
	}
}

