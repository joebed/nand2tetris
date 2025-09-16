#pragma once

#include <fstream>
#include <string>

#include "types.h"
using namespace types;

class CodeWriter
{
public:
	CodeWriter() = default;

	void set_output_stream(const std::string& output_filename);
	void close();
	void write_arithmetic(const CommandType command, const std::string& segment);
	void write_push_pop(const CommandType command, const std::string& segment, const int index);
private:
	std::ofstream fout_;
};

