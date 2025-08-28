#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "parser.h"

Parser::Parser(const std::string& input_filename)
	: fin_(input_filename)
	, has_more_commands_(true)
{}


void Parser::first_pass()
{
	while (advance())
	{
		std::string s;
		if (command_type() != CommandType::C && (s = symbol()).size() != 0)
		{
			symbol_table_.add_symbol(s, std::nullopt);
		}
	}

	has_more_commands_ = true;
	fin_.clear();
	fin_.seekg(0);
}

void Parser::second_pass()
{

}

bool Parser::Parser::advance()
{
	if (!has_more_commands_)
	{
		throw std::runtime_error("No more commands but advance called");
	}
	if (!std::getline(fin_, curr_command_))
	{
		has_more_commands_ = false;
		curr_command_ = "done"; // forces the curr_command size to be > 0 so i can practice 1 point of exit
	}
	else
	{
		curr_command_ = curr_command_.substr(0, curr_command_.find("//"));
		curr_command_.erase(std::remove_if(curr_command_.begin()
					, curr_command_.end()
					, [](unsigned char c) { return std::isspace(c); })
				, curr_command_.end());
	}
	
	return (curr_command_.size() != 0) // if curr_command_.size() == 0, then line is empty or comment only
		? has_more_commands_
		: advance();
}

CommandType Parser::command_type()
{
	if (curr_command_.front() == '@')
	{
		return CommandType::A;
	}
	if (curr_command_.front() == '(')
	{
		return CommandType::L;
	}
	return CommandType::C;
}

std::string Parser::symbol()
{
	std::string symbol;
	switch (command_type())
	{
		case CommandType::A:
			{
				symbol = curr_command_.substr(1);
				if (!isalpha(symbol[0]))
				{
					symbol = "";
				}
				break;
			}
		case CommandType::L:
			{
				const size_t end_of_label = curr_command_.find(')');
				if (end_of_label == std::string::npos)
				{
					std::string e_msg = "label doesn't have end ), fix formatting for '" + curr_command_ + "'";
					throw std::runtime_error(e_msg);
				}
				symbol = curr_command_.substr(1, end_of_label - 2); // -2 to account for both ( and )
				break;
			}
		case CommandType::C:
			throw std::runtime_error("Tried to access symbol of C instruction");
	}
	return symbol;
}

Instruction Parser::process_instruction()
{
	switch (command_type())
	{
		case CommandType::A:
			return process_a_instruction();
		case CommandType::C:
			process_c_instruction();
			break;
		case CommandType::L:
			process_l_instruction();
			break;
	}
}

Instruction Parser::process_c_instruction()
{
	Instruction ins(0b1110'0000'0000'0000);
	size_t curr_val = 0;
	size_t equal_pos = curr_command_.find('=');
	if (equal_pos != std::string::npos)
	{
		ins |= Code::dest_ins(curr_command_.substr(curr_val, equal_pos));

		curr_val += equal_pos + 1;
	}

	size_t semi_pos = curr_command_.find(';');
	ins |= Code::comp_ins(curr_command_.substr(curr_val, semi_pos));

	if (semi_pos != std::string::npos)
	{
		ins |= Code::jump_ins(curr_command_.substr(semi_pos + 1));
	}

	return ins;
}

Instruction process_a_instruction(const std::string& line)
{
	Instruction ins = std::stoul(line.substr(1)); // substr 1 is to remove the @
	if ((ins >> 15) == 1)
	{
		std::string e = "Error: A instructions cant be >= 2^15";
		std::cerr << e << "\n";
		throw std::runtime_error(e);
	}
	return ins;
}




