#include<iostream>
#include "Lexer.hpp"
#include "Parser.hpp"
#include "CodeGenerator.hpp"

int main() 
{
	std::ifstream inputFile("mycode.xx");  // Ensure the file is open

	// Check if the file was successfully opened
	if (!inputFile) {
		std::cerr << "Error opening file!" << std::endl;
		return 1; // Return an error code
	}

	std::string sourceCode((std::istreambuf_iterator<char>(inputFile)),
		std::istreambuf_iterator<char>());

	inputFile.close();

	Lexer lexer(sourceCode);

	Parser parser(lexer);

	Parser::ASTNode* ast = parser.parseProgram();

	CodeGenerator codegen;

	codegen.generate(ast, "output.cpp");


	// free all the pointers in the nested vectors
	for (Parser::ASTNode* ptr : ast->tree)
	{
		if (Parser::FunctionNode* funcptr = dynamic_cast<Parser::FunctionNode*>(ptr))
		{
			for (Parser::ASTNode* ptr : funcptr->body)
			{
				delete ptr;
			}
		}

		delete ptr;
	}

	delete ast;

	system("g++ -o output output.cpp");
	system(".\\output.exe");

	return 0;
}