#include <algorithm>
#include <bitset>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

using Instruction = std::bitset<16>;

std::unordered_map<std::string, Instruction> COMP_MAP = {
	{"0",   Instruction(0b0101010) << 6},
	{"1",   Instruction(0b0111111) << 6},
	{"-1",  Instruction(0b0111010) << 6},
	{"D",   Instruction(0b0001100) << 6},
	{"A",   Instruction(0b0110000) << 6},
	{"M",   Instruction(0b1110000) << 6},
	{"!D",  Instruction(0b0001101) << 6},
	{"!A",  Instruction(0b0110001) << 6},
	{"!M",  Instruction(0b1110001) << 6},
	{"-D",  Instruction(0b0001111) << 6},
	{"-A",  Instruction(0b0110011) << 6},
	{"-M",  Instruction(0b1110011) << 6},
	{"D+1", Instruction(0b0011111) << 6},
	{"A+1", Instruction(0b0110111) << 6},
	{"M+1", Instruction(0b1110111) << 6},
	{"D-1", Instruction(0b0001110) << 6},
	{"A-1", Instruction(0b0110010) << 6},
	{"M-1", Instruction(0b1110010) << 6},
	{"D+A", Instruction(0b0000010) << 6},
	{"D+M", Instruction(0b1000010) << 6},
	{"D-A", Instruction(0b0010011) << 6},
	{"D-M", Instruction(0b1010011) << 6},
	{"A-D", Instruction(0b0000111) << 6},
	{"M-D", Instruction(0b1000111) << 6},
	{"D&A", Instruction(0b0000000) << 6},
	{"D&M", Instruction(0b1000000) << 6},
	{"D|A", Instruction(0b0010101) << 6},
	{"D|M", Instruction(0b1010101) << 6},
};

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

Instruction process_a_instruction(const std::string& line)
{
	Instruction ins = std::stoul(line.substr(1)); // substr 1 is to remove the @
	if (ins >> 15 == 1)
	{
		std::string e = "Error: A instructions cant be >= 2^15";
		std::cerr << e << "\n";
		throw std::runtime_error(e);
	}
	return ins;
}

Instruction dest_ins(const std::string& dest_val)
{
	Instruction return_val(0);
	if (dest_val.find('M') != std::string::npos)
	{
		return_val.set(3);
	}
	if (dest_val.find('D') != std::string::npos)
	{
		return_val.set(4);
	}
	if (dest_val.find('A') != std::string::npos)
	{
		return_val.set(5);
	}
	return return_val;
}

Instruction comp_ins(const std::string& comp_val)
{
	auto it = COMP_MAP.find(comp_val);
	if (it == COMP_MAP.end())
	{
		std::string s = "Error: " + comp_val + " not found in comp map. Check assembly file for accuracy";
		throw std::runtime_error(s);
	}
	return it->second;
}

Instruction jump_ins(const std::string& jump_val)
{
	if (jump_val == "JMP")
	{
		return Instruction(0b111);
	}
	if (jump_val == "JNE")
	{
		return Instruction(0b101);
	}

	Instruction return_val = 0;
	if (jump_val.find('G') != std::string::npos)
	{
		return_val.set(0);
	}
	if (jump_val.find('E') != std::string::npos)
	{
		return_val.set(1);
	}
	if (jump_val.find('L') != std::string::npos)
	{
		return_val.set(2);
	}
	return return_val;
}

Instruction process_c_instruction(const std::string& line)
{
	Instruction ins(0b1110'0000'0000'0000);
	size_t curr_val = 0;
	size_t equal_pos = line.find('=');
	if (equal_pos != std::string::npos)
	{
		ins |= dest_ins(line.substr(curr_val, equal_pos));

		curr_val += equal_pos + 1;
	}

	size_t semi_pos = line.find(';');
	ins |= comp_ins(line.substr(curr_val, semi_pos));

	if (semi_pos != std::string::npos)
	{
		ins |= jump_ins(line.substr(semi_pos + 1));
	}

	return ins;
}


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "usage: hack_assembler <assembly file with .asm extension>\n";
		return 1;
	}
	
	std::string input_filename = argv[1];
	std::string output_filename = get_output_file(input_filename);
	std::ifstream fin(input_filename);
	std::ofstream fout(output_filename);

	std::string s;
	while (std::getline(fin, s))
	{
		s = s.substr(0, s.find("//"));
		if (s.size() == 0)
		{
			continue;
		}
		s.erase(std::remove_if(s.begin()
					, s.end()
					, [](unsigned char c) { return std::isspace(c); })
				, s.end());
		if (s.size() == 0)
		{
			continue;
		}

		
		std::cout << "working on '" << s << "'\t\t";
		Instruction ins;
		bool is_a_instruction = s.front() == '@';
		ins = (is_a_instruction)
			? process_a_instruction(s)
			: process_c_instruction(s);

		std::cout << ((is_a_instruction) ? ins.to_ulong() : ins) << "\n";
		fout << ins << "\n";
	}

	std::cout << "Success! Output written to " << output_filename << "\n";
	return 0;
}

