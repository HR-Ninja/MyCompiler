#ifndef LEXER
#define LEXER

#include<iostream>
#include<string>

class Lexer
{
private:
	std::string src;
	int position;


public:

	enum tokenType
	{
		TOKEN_VOID,
		TOKEN_FUNC,
		TOKEN_IDENTIFIER,
		TOKEN_PRINT,
		TOKEN_STRING_LITERAL,
		TOKEN_LPAREN,
		TOKEN_RPAREN,
		TOKEN_LBRACE,
		TOKEN_RBRACE,
		TOKEN_SEMICOLON,
		TOKEN_EOF
	};

	struct Token
	{
		tokenType type;
		std::string value;
	};


	Lexer(const std::string& src);

	Token nextToken();
	std::string getWord();
	std::string getLiteral();

	void debugPrint();

};





#endif // !LEXER
