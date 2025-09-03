#include <stdexcept>

#include "symbol_table.h"

SymbolTable::SymbolTable()
{
	// TODO: get a plugin to align commas
	symbol_to_address_ = std::unordered_map<std::string, uint32_t>({
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

void SymbolTable::add_symbol(const std::string& symbol, std::optional<uint32_t> address)
{
	if (address)
	{
		auto it = symbol_to_address_.find(symbol);
		if (it != symbol_to_address_.end())
		{
			std::string e = "tried explicitly setting address of already defined symbol: " + symbol;
			throw std::runtime_error(e);
		}
		auto it2 = used_addresses_.find(address.value());
		if (it2 != used_addresses_.end()) // This should never get triggered
		{
			std::string e = "tried setting address " + std::to_string(address.value()) + " multiple times";
			throw std::runtime_error(e);
		}
		symbol_to_address_[symbol] = address.value();
		used_addresses_.insert(address.value());
	}
	else
	{
		symbols_requiring_addresses_.insert(symbol);
	}
}

void SymbolTable::assign_remaining_symbols()
{
	uint32_t next_unused_address = 0x10;
	auto address_it = used_addresses_.begin();
	while (address_it != used_addresses_.end() && *address_it < next_unused_address) address_it++;
	for (auto symbol_it = symbols_requiring_addresses_.begin(); symbol_it != symbols_requiring_addresses_.end(); ++symbol_it)
	{
		if (symbol_to_address_.find(*symbol_it) != symbol_to_address_.end())
			continue;
		while (address_it != used_addresses_.end() && next_unused_address == *address_it)
		{
			next_unused_address++;
			address_it++;
		}
		symbol_to_address_[*symbol_it] = next_unused_address++;
	}
}

uint32_t SymbolTable::decode_symbol(const std::string& symbol)
{
	auto it = symbol_to_address_.find(symbol);
	if (it == symbol_to_address_.end())
	{
		std::string e = "Fail to find symbol " + symbol;
		throw std::runtime_error(e);
	}
	return it->second;
}

