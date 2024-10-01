#include "Lexer.hpp"


Lexer::Lexer(const std::string& src) : src(src), position(0) {};

Lexer::Token Lexer::nextToken()
{

	while (position < src.size())
	{
		char current = src[position];

		// skip whitespaces
		if (isspace(current))
		{
			position++;
			continue;
		}

		if (isalpha(current))
		{
			std::string word = getWord();
			std::cout << "tokenized word: " << word << std::endl;

			if (word == "void") return { TOKEN_VOID, word };
			if (word == "func") return { TOKEN_FUNC, word };
			if (word == "print") return { TOKEN_PRINT, word };

			return { TOKEN_IDENTIFIER, word };
		}

		if (current == '"')
		{
			std::string literal = getLiteral();
			std::cout << "tokenized string literal: " << literal << std::endl;
			return { TOKEN_STRING_LITERAL, literal };
		}


		switch (current)
		{
			case '(':
				position++;
				std::cout << "tokenized item: (\n";
				return { TOKEN_LPAREN, "(" };
			case ')':
				position++;
				std::cout << "tokenized item: )\n";
				return { TOKEN_RPAREN, ")" };
			case '{':
				position++;
				std::cout << "tokenized item: {\n";
				return { TOKEN_LBRACE, "{" };
			case '}':
				position++;
				std::cout << "tokenized item: }\n";
				return { TOKEN_RBRACE, "}" };
			case ';':
				position++;
				std::cout << "tokenized item: ;\n";
				return { TOKEN_SEMICOLON, ";" };
		}
			
		std::cerr << "unknown charecter: " << current << std::endl;
		position++;
	}

	return { TOKEN_EOF, "EOF" };
}


std::string Lexer::getWord()
{
	int start = position;
	while (isalpha(src[position]))
	{
		position++;
	}

	return src.substr(start, position - start);
}


std::string Lexer::getLiteral()
{
	position++; // skip opening quotes
	int start = position;

	while (position < src.size() && src[position] != '"')
	{
		position++;
	}

	if (position < src.size() && src[position] == '"')
	{
		std::string literal = src.substr(start, position - start);
		position++;
		return literal;
	}
	else
	{
		std::cerr << "unknown string literal " << std::endl;
		return "";
	}
}


void Lexer::debugPrint()
{
	Token t;

	while (true)
	{
		if (t.type == TOKEN_EOF) break;

		t = nextToken();
	}
}


