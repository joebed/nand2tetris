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
	void write_command(const CommandType command, const std::optional<SegmentType>& segment, const std::optional<int>& index);
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
	void push_D_to_stack();
	void goto_top_of_stack();

	// Sets D to whatever the top of the stack and decrements sp
	void pop_from_stack();

	void move_A_to_segment_and_offset(const SegmentType segment, const int index);

	// Affects all registers, 0x0000 is stored in R13, 0xFFFF is stored in R14
	void set_boolean_registers();

	void set_D_to_constant(const int constant);
	
	// Initialization, debugging fn
	void segment_initialization(const std::string& segment, const int starting_point);

	void write_add_command();
	void write_sub_command();
	void write_neg_command();
	void write_eq_command();
	void write_gt_command();
	void write_lt_command();
	void write_and_command();
	void write_or_command();
	void write_not_command();
	void write_push_command(const SegmentType segment, const int index);
	void write_pop_command(const SegmentType segment, const int index);
	void write_label_command();
	void write_goto_command();
	void write_if_command();
	void write_function_command();
	void write_return_command();
	void write_call_command();
};



} // namespace vm_translator
 
