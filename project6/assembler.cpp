#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "assembler.h"

namespace
{
std::string get_output_file(const std::string& input_filename)
{
	size_t ext = input_filename.find(".asm");
	if (ext == std::string::npos)
	{
		std::cerr << "usage: hack_assembler <assembly file with .asm extension>\n";
		throw std::runtime_error("bruh");
	}
	return input_filename.substr(0, ext) + ".hack";
}
}

Assembler::Assembler(const std::string& input_filename)
	: input_filename_(input_filename)
	, fin_(input_filename)
{}

void Assembler::assemble()
{
	first_run();
	second_run();
}

void Assembler::first_run()
{
	std::optional<std::string> s;
	size_t line_number = 0;
	while ((s = advance()))
	{
		CommandType command = command_type(s.value());
		
		std::optional<std::string> symbol = try_get_symbol(s.value(), command);
		switch (command)
		{
			case CommandType::A:
				if (symbol)
				{
					symbol_table_.add_symbol(symbol.value());
				}
				[[fallthrough]];
			case CommandType::C:
				++line_number;
				break;
			case CommandType::L:
				if (symbol)
				{
					symbol_table_.add_symbol(symbol.value(), line_number);
				}
		}
	}
	symbol_table_.assign_remaining_symbols();
	fin_.clear();
	fin_.seekg(0);
}

void Assembler::second_run()
{
	std::optional<std::string> s;
	std::ofstream fout(get_output_file(input_filename_));
	while ((s = advance()))
	{
		CommandType command = command_type(s.value());
		if (command == CommandType::A)
		{
			fout << process_a_instruction(s.value()) <<  "\n";
		}
		else if (command == CommandType::C)
		{
			fout << process_c_instruction(s.value()) <<  "\n";
		}
	}
}

std::optional<std::string> Assembler::advance()
{
	std::string s;
	if (!std::getline(fin_, s))
	{
		return std::nullopt;
	}
	else
	{
		s = s.substr(0, s.find("//"));
		s.erase(std::remove_if(s.begin()
					, s.end()
					, [](unsigned char c) { return std::isspace(c); })
				, s.end());
	}
	
	return (s.size() != 0) // if s.size() == 0, then line is empty or comment only
		? s
		: advance();
}

Instruction Assembler::process_c_instruction(const std::string& line)
{
	Instruction ins(0b1110'0000'0000'0000);
	size_t curr_val = 0;
	size_t equal_pos = line.find('=');
	if (equal_pos != std::string::npos)
	{
		ins |= Code::dest_ins(line.substr(curr_val, equal_pos));

		curr_val += equal_pos + 1;
	}

	size_t semi_pos = line.find(';');
	ins |= Code::comp_ins(line.substr(curr_val, semi_pos));

	if (semi_pos != std::string::npos)
	{
		ins |= Code::jump_ins(line.substr(semi_pos + 1));
	}

	return ins;
}

Instruction Assembler::process_a_instruction(const std::string& line)
{
	std::optional<std::string> s = try_get_symbol(line, CommandType::A);
	Instruction ins = (s)
		? symbol_table_.decode_symbol(s.value())
		: std::stoul(line.substr(1)); // substr 1 is to remove the @
									  
	if ((ins >> 15) == 1)
	{
		std::string e = "Error: A instructions cant be >= 2^15";
		std::cerr << e << "\n";
		throw std::runtime_error(e);
	}
	return ins;
}


CommandType Assembler::command_type(const std::string& line)
{
	if (line[0] == '@')
		return CommandType::A;
	if(line[1] == '(')
		return CommandType::L;
	return CommandType::C;
}

std::optional<std::string> Assembler::try_get_symbol(const std::string& line, CommandType command_type)
{
	switch (command_type)
	{

	case CommandType::A:
	{
		if (std::isdigit(line[1]))
			return std::nullopt;

		return line.substr(1);
	}

	case CommandType::L:
		return line.substr(1, line.size() - 2);

	default:
		return std::nullopt;
	}
}



