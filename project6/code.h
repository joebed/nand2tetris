#include <bitset>
#include <string>
#include <unordered_map>

using Instruction = std::bitset<16>;

class Code
{
public:
	static Instruction dest_ins(const std::string& dest_val);
	static Instruction comp_ins(const std::string& comp_val);
	static Instruction jump_ins(const std::string& jump_val);

private:
	static inline std::unordered_map<std::string, Instruction> COMP_MAP = {
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
};


