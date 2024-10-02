#ifndef CODEGEN
#define CODEGEN

#include<fstream>
#include "Parser.hpp"

class CodeGenerator
{
public:
	void generate(Parser::ASTNode*& ast, const std::string& outputFileName);
};


#endif // !CODEGEN