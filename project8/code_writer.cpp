#include <stdexcept>
#include <iostream>

#include "code_writer.h"

namespace vm_translator
{
CodeWriter::CodeWriter()
	: eq_counter_{0}
	, gt_counter_{0}
	, lt_counter_{0}
{}

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

	curr_filebase_ = std::string(curr_filebase_.begin() + curr_filebase_.find_last_of('/') + 1, curr_filebase_.end());

	if (curr_filebase_ == "MyTest")
	{
		segment_initialization("SP", 256);
		segment_initialization("LCL", 300);
		segment_initialization("ARG", 400);
		segment_initialization("THIS", 3000);
		segment_initialization("THAT", 3010);
	}
}

void CodeWriter::close()
{
	fout_ << "(END)\n"
		<< "@END\n"
		<< "0;JMP\n"
		<< "(" << true_label << ")\n";
	fout_ << "D=-1\n";
	fout_ << "@JUMP_TO_PREVIOUS\n"
		<< "0;JMP\n"
		<< "(" << false_label << ")\n";
	fout_ << "D=0\n";
	fout_ << "(JUMP_TO_PREVIOUS)\n"
		<< "@R15\n"
		<< "A=M\n"
		<< "0;JMP\n";
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
			std::cerr << command << "\n";
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
	fout_ << "@SP\n"
		<< "M=M+1\n";
}

void CodeWriter::decrement_stack_pointer()
{
	fout_ << "@SP\n"
		<< "M=M-1\n";
}

void CodeWriter::push_D_to_stack()
{
	increment_stack_pointer();
	goto_top_of_stack();
	fout_ << "M=D\n";
}

void CodeWriter::goto_top_of_stack()
{
	fout_ << "@SP\n"
		<< "A=M-1\n";
}

void CodeWriter::pop_from_stack()
{
	decrement_stack_pointer();
	fout_ << "A=M\n"
		<< "D=M\n";
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
			fout_ << "@" << static_symbol(index) << "\n";
			break;
		case (SegmentType::TEMP):
			static constexpr int TEMP_BASE = 5;
			fout_ << "@" << 5 + index << "\n";
			break;
		default:
			set_D_to_constant(index);
			fout_ << "@" << types::segment_to_reg_name(segment) << "\n"
				<< "A=D+M\n";
			break;
	}
}

void CodeWriter::set_R15_to_label(std::string_view label_to_return_to)
{
	fout_ << "@" << label_to_return_to << "\n"
		<< "D=A\n"
		<< "@R15\n"
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
	fout_ << "A=A-1\n"
		<< "M=D+M\n";
}

void CodeWriter::write_sub_command()
{
	pop_from_stack();
	fout_ << "A=A-1\n"
		<< "M=M-D\n";
}

void CodeWriter::write_neg_command()
{
	goto_top_of_stack();
	fout_ << "M=-M\n";
}

void CodeWriter::true_false_handler(std::string_view jump_command)
{
	fout_ << "D=M-D\n"
		<< "@" << true_label << "\n"
		<< "D;" << jump_command << "\n"
		<< "@" << false_label << "\n"
		<< "0;JMP\n";
}


void CodeWriter::conditional_handler(std::string_view label, std::string_view jump_command)
{
	set_R15_to_label(label);
	pop_from_stack();
	goto_top_of_stack();
	true_false_handler(jump_command);
	place_label(label);
	goto_top_of_stack();
	fout_ << "M=D\n";
}

void CodeWriter::write_eq_command()
{
	const std::string label = curr_filebase_ + ".EQ_" + std::to_string(eq_counter_++);
	conditional_handler(label, "JEQ");
}

void CodeWriter:: write_gt_command()
{
	const std::string label = curr_filebase_ + ".GT_" + std::to_string(gt_counter_++);
	conditional_handler(label, "JGT");
}

void CodeWriter:: write_lt_command()
{
	const std::string label = curr_filebase_ + ".LT_" + std::to_string(lt_counter_++);
	conditional_handler(label, "JLT");
}

void CodeWriter:: write_and_command()
{
	pop_from_stack();
	fout_ << "A=A-1\n"
		<< "M=D&M\n";
}

void CodeWriter:: write_or_command()
{
	pop_from_stack();
	fout_ << "A=A-1\n"
		<< "M=D|M\n";
}

void CodeWriter:: write_not_command()
{
	goto_top_of_stack();
	fout_ << "M=!M\n";
}

void CodeWriter::write_push_command(const SegmentType segment, const int index)
{
	if (segment == SegmentType::CONSTANT)
	{
		set_D_to_constant(index);
		push_D_to_stack();
	}
	else
	{
		move_A_to_segment_and_offset(segment, index);
		fout_ << "D=M\n";
		push_D_to_stack();
	}
}

void CodeWriter::write_pop_command(const SegmentType segment, const int index)
{
	move_A_to_segment_and_offset(segment, index);
	fout_ << "D=A\n"
		<< "@R13\n"
		<< "M=D\n";
	pop_from_stack();
	fout_ << "@R13\n"
		<< "A=M\n"
		<< "M=D\n";

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

void CodeWriter::place_label(std::string_view s)
{
	fout_ << "(" << s << ")\n";
}

} // namespace vm_translator
 
