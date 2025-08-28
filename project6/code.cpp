#include <stdexcept>

#include "code.h"

Instruction Code::dest_ins(const std::string& dest_val)
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

Instruction Code::comp_ins(const std::string& comp_val)
{
	auto it = COMP_MAP.find(comp_val);
	if (it == COMP_MAP.end())
	{
		std::string s = "Error: " + comp_val + " not found in comp map. Check assembly file for accuracy";
		throw std::runtime_error(s);
	}
	return it->second;
}

Instruction Code::jump_ins(const std::string& jump_val)
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

