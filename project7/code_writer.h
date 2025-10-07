#pragma once

#include <fstream>
#include <string>
#include <optional>

#include "types.h"
using namespace types;

class CodeWriter
{
public:
	CodeWriter();

	void set_output_stream(const std::string& output_filename);
	void close();
	void write_arithmetic(const CommandType command, const SegmentType segment);
	void write_push_pop(const CommandType command, const SegmentType segment, const int index);
private:
	std::ofstream fout_;
	std::unordered_map<int, int> static_index_to_ram_address;
	int next_static_ram_address_;

	// Does not affect D
	// A finishes at SP
	void increment_stack_pointer();

	// Does not affect D
	// A finishes at SP
	void decrement_stack_pointer();


	// A finishes at SP
	void push_to_stack(std::optional<const int> constant = std::nullopt);
	// A finishes at SP
	void push_to_stack(const SegmentType segment, const int index);

	// Stores the top of stack to D, decrements stack pointer
	// A finishes at SP
	void pop_from_stack();

	// A finishes at SP
	void push_to_segment_from_stack(const SegmentType segment, const int index);
	void pop_from_segment_to_stack(const SegmentType segment, const int index);

	// Does not affect D
	// A finishes at SP
	void goto_top_of_stack();

	// A finishes at <constant>
	void set_D_to_constant(const int constant);

	void set_A_to_segment_index_translation(const SegmentType segment, const int index);
};

