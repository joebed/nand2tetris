#include <stdexcept>

#include "code_writer.h"

void CodeWriter::CodeWriter()
	: next_static_ram_address_(16)
{}

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

void CodeWriter::write_arithmetic(const CommandType command, const SegmentType segment)
{
}

void CodeWriter::write_push_pop(const CommandType command, const SegmentType segment, const int index)
{
	if (command != C_PUSH && command != C_PUSH)
	{
		throw std::runtime_error("Called write_push_pop on bad command"); // should never happen
	}
	if (command == C_PUSH)
	{
		if (segment == SegmentType::CONSTANT)
		{
			push_to_stack(index);
		}
		else
		{
			push_to_segment_from_stack(segment, index);
		}
	}

	// TODO: command is POP
	else
	{
		if (segment == SegmentType::CONSTANT)
		{
			throw std::runtime_error("Popping a constant doesnt make sense");
		}
		pop_from_segment_to_stack(segment, index);
	}

}



void CodeWriter::increment_stack_pointer()
{
	fout_ << "@SP\nM=M+1\n";
}

void CodeWriter::decrement_stack_pointer()
{
	fout_ << "@SP\nM=M-1\n";
}

void CodeWriter::goto_top_of_stack()
{
	fout_ << "@SP\nA=M\n";
}

void CodeWriter::pop_from_stack()
{
	decrement_stack_pointer();
	fout_ << "A=M\nD=M\n";
}

void CodeWriter::set_D_to_constant(const int constant)
{
	fout_ << "@" << constant << "\nD=A\n";
}

// TODO: stack and temp translations
void CodeWriter::push_to_segment_from_stack(const SegmentType segment, const int index)
{
	set_D_to_constant(index);
	fout_ << "@" << types::segment_to_reg_name(segment) << "\n\
		D=D+M\n\
		@R13\n\
		M=D\n";
	pop_from_stack();
	fout_ << "@R13\nA=M\nM=D\n";
}


void CodeWriter::push_to_stack(std::optional<const int> constant)
{
	if (constant.has_value())
	{
		set_D_to_constant(index);
	}
	goto_top_of_stack();
	fout_ << "M=D\n";
	increment_stack_pointer();
}

void CodeWriter::push_to_stack(const SegmentType segment, const int index)
{
	// First translate segment and index to the correct address, store it as D
	set_D_to_constant(index);
	set_A_to_segment_index_translation(segment)
	fout_ << "D=M\n";
	push_to_stack();
}

void CodeWriter::pop_from_segment_to_stack(const SegmentType segment, const int index)
{

}

void CodeWriter::set_A_to_segment_index_translation(const SegmentType segment)
{
	if (segment == SegmentType::STATIC)
	{
		fout_ << "@" << get_addr_for_static_index(index) << "\n";
		return;
	}
		fout_ << "@" << types::segment_to_reg_name(segment) << "\n"
			<< "A="
			<< ((segment == SegmentType::THIS || segment == SegmentType::THAT)
				? "M"
				: "D+M")
			<< "\n";
}

