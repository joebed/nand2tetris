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

void CodeWriter::write_command_base(const CommandType command, const std::optional<SegmentType>& segment, const std::optional<int>& index)
{
	switch (command)
	{
		case (CommandType::ADD):
			// write_command<CommandType::ADD>();
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

void CodeWriter::segment_initialization(const std::string& segment, const int starting_point)
{
	write_comment(segment + " initialization");
	set_D_to_constant(starting_point);
	fout_ << "@" << segment << "\n"
		<< "M=D\n";
}

} // namespace vm_translator
 
