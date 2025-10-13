#include <stdexcept>
#include <iostream>

#include "code_writer.h"

namespace vm_translator
{
void CodeWriter::set_output_stream(const std::string& input_filename)
{
	if (input_filename == "")
	{
		throw std::runtime_error("Output filename not specified");
	}
	size_t base_filename_end = input_filename.find(".vm");
	if (base_filename_end == std::string::npos)
	{
		std::string e = "Input filename (" + input_filename + ") does not end in '.vm'";
		throw std::runtime_error(e);
	}
	curr_filebase_ = input_filename.substr(0, base_filename_end);

	std::string output_filename = curr_filebase_ + ".asm";
	std::cout << "Writing output to " << output_filename << "\n";
	fout_ = std::ofstream(output_filename);

	segment_initialization("SP", 256);
	segment_initialization("LCL", 300);
	segment_initialization("ARG", 400);
	segment_initialization("THIS", 3000);
	segment_initialization("THAT", 3010);
}

void CodeWriter::close()
{
	fout_ << "(END)\n@END\n0;JMP\n";
	fout_.close();
	fout_ = std::ofstream();
}

void CodeWriter::write_command(const CommandType command, const std::optional<SegmentType>& segment, const std::optional<int>& index)
{
	switch (command)
	{
		case (CommandType::ADD):
			write_add_command();
			break;
		case (CommandType::SUB):
			write_sub_command();
			break;
		case (CommandType::NEG):
			write_neg_command();
			break;
		case (CommandType::EQ):
			write_eq_command();
			break;
		case (CommandType::GT):
			write_gt_command();
			break;
		case (CommandType::LT):
			write_lt_command();
			break;
		case (CommandType::AND):
			write_and_command();
			break;
		case (CommandType::OR):
			write_or_command();
			break;
		case (CommandType::NOT):
			write_not_command();
			break;
		case (CommandType::PUSH):
			// TODO: error handling on the optionals
			write_push_command(segment.value(), index.value());
			break;
		case (CommandType::POP):
			write_pop_command(segment.value(), index.value());
			break;
		case (CommandType::LABEL):
			write_label_command();
			break;
		case (CommandType::GOTO):
			write_goto_command();
			break;
		case (CommandType::IF):
			write_if_command();
			break;
		case (CommandType::FUNCTION):
			write_function_command();
			break;
		case (CommandType::RETURN):
			write_return_command();
			break;
		case (CommandType::CALL):
			write_call_command();
			break;
		default:
			throw std::runtime_error("Not implemented");
}
}

void CodeWriter::write_comment(const std::string& line)
{
	fout_ << "// " << line << "\n";
}

std::string CodeWriter::static_symbol(const int index)
{
	return curr_filebase_ + "." + std::to_string(index);
}

void CodeWriter::increment_stack_pointer()
{
	fout_ << "@SP\nM=M+1\n";
}

void CodeWriter::decrement_stack_pointer()
{
	fout_ << "@SP\nM=M-1\n";
}

void CodeWriter::push_D_to_stack()
{
	goto_top_of_stack();
	fout_ << "M=D\n";
	increment_stack_pointer();
}

void CodeWriter::goto_top_of_stack()
{
	fout_ << "@SP\n"
		<< "A=M\n";
}

void CodeWriter::pop_from_stack()
{
	decrement_stack_pointer();
	fout_ << "A=M\nD=M\n";
}

void CodeWriter::move_A_to_segment_and_offset(const SegmentType segment, const int index)
{
	switch (segment)
	{
		case (SegmentType::POINTER_THIS):
			fout_ << "@THIS\n";
			break;
		case (SegmentType::POINTER_THAT):
			fout_ << "@THAT\n";
			break;
		case (SegmentType::STATIC):
			fout_ << "@
		default:
			set_D_to_constant(index);
			fout_ << "@" << types::segment_to_reg_name(segment) << "\n"
				<< "A=A+D\n";
			break;
	}
}

void CodeWriter::set_boolean_registers()
{
	set_D_to_constant(0);
	fout_ << "@R13\n"
		<< "M=D\n";
	set_D_to_constant(0xFFFF);
	fout_ << "@R14\n"
		<< "M=D\n";
}

void CodeWriter::set_D_to_constant(const int constant)
{
	fout_ << "@" << constant << "\n"
		<< "D=A\n";
}

void CodeWriter::segment_initialization(const std::string& segment, const int starting_point)
{
	write_comment(segment + " initialization");
	set_D_to_constant(starting_point);
	fout_ << "@" << segment << "\n"
		<< "M=D\n";
}

// Don't really need to pop twice, then push. Just need to pop once then add D to the current M
void CodeWriter::write_add_command()
{
	pop_from_stack();
	fout_ << "M=D+M\n";
}

void CodeWriter::write_sub_command()
{
	pop_from_stack();
	fout_ << "M=M-D\n";
}

void CodeWriter::write_neg_command()
{
	goto_top_of_stack();
	fout_ << "M=-M\n";
}

// 
void CodeWriter:: write_eq_command()
{
	set_boolean_registers();
	pop_from_stack();
	goto_top_of_stack();

	// TODO: Figure out how this sp to work
	fout_ << "D=D-M\n";
	// 	<< "@R14\n"
	// 	<< "JET
}

void CodeWriter:: write_gt_command()
{
	pop_from_stack();
}

void CodeWriter:: write_lt_command()
{
	pop_from_stack();
}

void CodeWriter:: write_and_command()
{
	pop_from_stack();
	fout_ << "M=M&D\n";
}

void CodeWriter:: write_or_command()
{
	pop_from_stack();
	fout_ << "M=M|D\n";
}

void CodeWriter:: write_not_command()
{
	goto_top_of_stack();
	fout_ << "M=!M\n";
}

void CodeWriter::write_push_command(const SegmentType segment, const int index)
{
	if (segment != SegmentType::CONSTANT)
	{
		set_D_to_constant(index);
	}
	else
	{
		move_A_to_segment_and_offset(segment, index);
		fout_ << "D=M\n";
	}
	push_D_to_stack();
}

void CodeWriter::write_pop_command(const SegmentType segment, const int index)
{

}

void CodeWriter::write_label_command()
{
}

void CodeWriter:: write_goto_command()
{
}

void CodeWriter:: write_if_command()
{
}

void CodeWriter:: write_function_command()
{
}

void CodeWriter:: write_return_command()
{
}

void CodeWriter:: write_call_command()
{
}

} // namespace vm_translator
 
