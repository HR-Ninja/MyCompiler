#include "Parser.hpp"

Parser::Parser(Lexer& lex) : lexer(lex)
{
	currentToken = lexer.nextToken();
}

Parser::ASTNode* Parser::parseProgram()
{
	ASTNode* root = new ASTNode();

	if (currentToken.type != Lexer::TOKEN_FUNC)
	{
		std::cerr << "Missing token type: func" << std::endl;
		exit(1);
	}

	KeywordNode* keyword = new KeywordNode();
	keyword->name = currentToken.value;

	root->tree.push_back(std::move(keyword));

	currentToken = lexer.nextToken();

	if (currentToken.type != Lexer::TOKEN_IDENTIFIER)
	{
		std::cerr << "Missing token type: identifier" << std::endl;
		exit(1);
	}

	FunctionNode* func = new FunctionNode();
	func->name = currentToken.value;

	// ignore paremters for now and skip ahead
	currentToken = lexer.nextToken();
	currentToken = lexer.nextToken();
	currentToken = lexer.nextToken();
	currentToken = lexer.nextToken();

	while (currentToken.type != Lexer::TOKEN_RBRACE)
	{
		func->body.push_back(std::move(parseStatement()));
	}

	root->tree.push_back(std::move(func));

	return root;
}

Parser::ASTNode* Parser::parseStatement()
{
	if (currentToken.type == Lexer::TOKEN_PRINT)
	{
		// skip ahead
		currentToken = lexer.nextToken();
		currentToken = lexer.nextToken();

		PrintNode* printNode = new PrintNode();
		printNode->message = currentToken.value;

		// skip head again
		currentToken = lexer.nextToken(); 
		currentToken = lexer.nextToken();
		currentToken = lexer.nextToken();

		return printNode;
	}

	return nullptr;
}