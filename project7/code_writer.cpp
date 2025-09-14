#include <stdexcept>

#include "code_writer.h"

void CodeWriter::set_output_stream(const std::string& output_filename)
{
	fout_ = std::ofstream(output_filename);
}

void CodeWriter::close()
{
	fout_ << "\n";
	fout_.close();
	fout_ = std::ofstream();
}

void CodeWriter::write_arithmetic(const std::string& command)
{
}

void CodeWriter::write_push_pop(const CommandType command, const std::string& segment, const int index)
{
	if (command != C_PUSH && command != C_PUSH)
	{
		throw std::runtime_error("Called write_push_pop on bad command"); // should never happen
	}

}

