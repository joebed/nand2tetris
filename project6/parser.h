#include <fstream>
#include <string>
#include <vector>

#include "code.h"
#include "symbol_table.h"

enum class CommandType
{
	A,
	C,
	L,
};

class Parser
{
public:
	Parser() = delete;
	Parser(const std::string& input_filename);

	void first_pass();
	void second_pass();
	
private:
	std::ifstream fin_;
	std::ofstream fout_;

	std::string curr_command_;
	
	SymbolTable symbol_table_;
	bool has_more_commands_;

	bool advance();
	CommandType command_type();
	std::string symbol();

	Instruction process_instruction();
	Instruction process_a_instruction();
	Instruction process_c_instruction();
	Instruction process_l_instruction();
};

