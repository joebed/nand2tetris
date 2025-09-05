#pragma once

#include <fstream>
#include <string>

#include "types.h"

class CodeWriter
{
public:
	CodeWriter(const std::string& output_filename);

	void write_arithmetic(const std::string& command);
	void write_push_pop(const CommandType command, const std::string& segment, const int index);
private:
	std::ofstream fout_;
};

