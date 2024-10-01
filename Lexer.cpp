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

			if (word == "func") return { TOKEN_FUNC, word };


		}







	}



	return { TOKEN_EOF, "EOF" };
}




