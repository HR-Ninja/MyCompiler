#ifndef PARSER
#define PARSER

#include<vector>
#include "Lexer.hpp"


class Parser
{
public:

	Lexer lexer;
	Lexer::Token currentToken;

	Parser(Lexer& lex);


	struct ASTNode
	{
		virtual ~ASTNode() = default;
		std::vector<ASTNode*> tree;
	};

	struct KeywordNode : public ASTNode
	{
		std::string name;
	};

	struct FunctionNode : public ASTNode
	{
		std::string name;
		std::vector<ASTNode*> body;
	};

	struct PrintNode : public ASTNode
	{
		std::string message;
	};

	ASTNode* parseProgram();
	ASTNode* parseStatement();

};



#endif // !PARSER