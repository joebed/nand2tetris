#include <fstream>
#include <functional>
#include <string>

#include "code.h"
#include "symbol_table.h"

enum class CommandType
{
	A,
	C,
	L,
};

class Assembler
{
public:
	Assembler() = delete;
	Assembler(const std::string& input_filename);

	void assemble();
private:
	std::string input_filename_;
	std::ifstream fin_;
	SymbolTable symbol_table_;

	void first_run();
	void second_run();

	std::optional<std::string> advance();

	Instruction process_c_instruction(const std::string& line);
	Instruction process_a_instruction(const std::string& line);
	CommandType command_type(const std::string& line);
	std::optional<std::string> try_get_symbol(const std::string& line, CommandType command_type);
};

