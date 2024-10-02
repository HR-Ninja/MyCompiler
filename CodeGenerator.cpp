#include "CodeGenerator.hpp"

void CodeGenerator::generate(Parser::ASTNode*& ast, const std::string& outputFileName)
{
	std::ofstream outputFile(outputFileName);

	if (!outputFile.is_open())
	{
		std::cerr << "Error opening output file" << std::endl;
		exit(1);
	}

	outputFile << "#include<iostream>\n";

	for (Parser::ASTNode* node : ast->tree)
	{

		if (Parser::KeywordNode* keywordNode = dynamic_cast<Parser::KeywordNode*>(node))
		{
			std::cout << "Found a KeywordNode with name: " << keywordNode->name << std::endl;
		}

		if (Parser::FunctionNode* funcNode = dynamic_cast<Parser::FunctionNode*>(node))
		{
			std::cout << "Found a FunctionNode with name: " << funcNode->name << std::endl;

			if (funcNode->name == "main")
			{
				outputFile << "int " << funcNode->name << "() {\n";
			}
			else
			{
				outputFile << funcNode->name << "() {\n";
			}

			for (Parser::ASTNode* statement : funcNode->body)
			{
				if (Parser::PrintNode* printNode = dynamic_cast<Parser::PrintNode*>(statement))
				{
					outputFile << "\tstd::cout << \"" << printNode->message << "\";\n";
				}
			}

			if (funcNode->name == "main") outputFile << "\treturn 0;\n";

			outputFile << "}";
		}
	}

	outputFile.close();
	
}
