#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>

class SymbolTable
{
public:
	SymbolTable();
	void add_symbol(const std::string& symbol, std::optional<uint32_t> address);
	uint32_t decode_symbol(const std::string& symbol);

private:
	std::unordered_map<std::string, uint32_t> symbol_to_index_;
	uint32_t next_available_index_;
};

