#include <cstdint>
#include <optional>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

class SymbolTable
{
public:
	SymbolTable();
	void add_symbol(const std::string& symbol, std::optional<uint32_t> address = std::nullopt);
	void assign_remaining_symbols();
	uint32_t decode_symbol(const std::string& symbol);

private:
	std::unordered_map<std::string, uint32_t> symbol_to_address_;
	std::set<uint32_t> used_addresses_;
	std::unordered_set<std::string> symbols_requiring_addresses_;
};

