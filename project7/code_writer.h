#pragma once

#include <fstream>
#include <string>
#include <optional>

#include "types.h"
using namespace types;

namespace vm_translator
{
class CodeWriter
{
public:
	CodeWriter() = default;

	void set_output_stream(const std::string& input_filename);
	void close();
	void write_command_base(const CommandType command, const std::optional<SegmentType>& segment, const std::optional<int>& index);
	void write_comment(const std::string& line);

private:
	std::ofstream fout_;
	std::string curr_filebase_;

	std::string static_symbol(const int index);

	// Does not affect D
	// A finishes at SP
	void increment_stack_pointer();

	// Does not affect D
	// A finishes at SP
	void decrement_stack_pointer();

	// Does not affect D
	// A finishes at SP
	void goto_top_of_stack();

	// Sets D to whatever the top of the stack and decrements sp
	void pop_from_stack();

	void set_D_to_constant(const int constant);
	
	// Initialization, debugging fn
	void segment_initialization(const std::string& segment, const int starting_point);

	// template <CommandType>
	// void write_command(const SegmentType segment, const int index);

	template <CommandType>
	void write_command();


};

// template <> void CodeWriter::write_command<CommandType::ADD>();

} // namespace vm_translator
 
#include "code_writer.ipp"

