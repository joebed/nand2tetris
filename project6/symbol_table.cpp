#include <stdexcept>

#include "symbol_table.h"

SymbolTable::SymbolTable()
	: next_available_index_(0x0010)
{
	// TODO: get a plugin to align commas
	symbol_to_index_ = std::unordered_map<std::string, uint32_t>({
			{"SP"  , 0x0000},
			{"LCL" , 0x0001},
			{"ARG" , 0x0002},
			{"THIS", 0x0003},
			{"THAT", 0x0004},
			{"R0"  , 0x0000},
			{"R1"  , 0x0001},
			{"R2"  , 0x0002},
			{"R3"  , 0x0003},
			{"R4"  , 0x0004},
			{"R5"  , 0x0005},
			{"R6"  , 0x0006},
			{"R7"  , 0x0007},
			{"R8"  , 0x0008},
			{"R9"  , 0x0009},
			{"R10" , 0x000A},
			{"R11" , 0x000B},
			{"R12" , 0x000C},
			{"R13" , 0x000D},
			{"R14" , 0x000E},
			{"R15" , 0x000F},
			{"SCREEN", 0x4000},
			{"KBD" , 0x6000},
	});
}

void SymbolTable::add_symbol(const std::string& symbol)
{
	auto it = symbol_to_index_.find(symbol);
	if (it == symbol_to_index_.end())
	{
		symbol_to_index_[symbol] = next_available_index_;
		++next_available_index_;
	}
}

uint32_t SymbolTable::decode_symbol(const std::string& symbol)
{
	auto it = symbol_to_index_.find(symbol);
	if (it == symbol_to_index_.end())
	{
		std::string e = "Fail to find symbol " + symbol;
		throw std::runtime_error(e);
	}
	return it->second;
}

