#include "pch.h"
#include "Parser.h"

//===============================
//========== Parser =============
//===============================

Parser::Parser(vector<Token>& tokens) : tokens(tokens), tok_idx(0), currentToken(nullptr)
{
	std::unique_ptr<vector<Node>> nodes = std::make_unique<vector<Node>>();
	advance();
}

void Parser::advance()
{

	if (tok_idx < tokens.size())
		currentToken = &tokens.at(tok_idx);

	++tok_idx;
}

string Parser::parse()
{
	std::shared_ptr<Node> nodeP = expr();
	return nodeP->represent();

}

// : INT|FLOAT
std::shared_ptr<Node> Parser::factor()
{
	
	const tokenTypes& type = currentToken->getType();

	if (type == tokenTypes::T_INT || type == tokenTypes::T_FLOAT) {
		std::shared_ptr<Node> node = std::make_shared<NumberNode>(*currentToken);
		advance();
		return node;
	}
	else { //Error
		std::shared_ptr<Node> node = std::make_shared<EmptyNode>(*currentToken);
		return node;
	}
		
	
}

// : factor ((MUL|DIV) factor)*
std::shared_ptr<Node> Parser::term()
{
	return bin_op([this]() { return this->factor(); }, tokenTypes::T_MULTIPLY, tokenTypes::T_DIVIDE);
}

// : term ((PLUS | MINUS) term)*
std::shared_ptr<Node> Parser::expr()
{
	return bin_op([this]() { return this->term(); }, tokenTypes::T_PLUS, tokenTypes::T_MINUS);
}

// : func ((op1 | op2) func)*
std::shared_ptr<Node> Parser::bin_op(std::function<std::shared_ptr<Node>()> func, tokenTypes op1, tokenTypes op2)
{

	std::shared_ptr<Node> left = func();

	tokenTypes type = currentToken->getType();

	while (type == op1 || type == op2)
	{
		//Incrementing
		Token* op_tok = currentToken;
		advance();
		//setting right
		std::shared_ptr<Node> right = func();
		//recursively chaining left to make a tree
		std::shared_ptr<BinOpNode> newNodePtr = std::make_shared<BinOpNode>(left, *op_tok, right);

		left = newNodePtr;
		
		type = currentToken->getType();
	}
	
	//returns final left tree
	return left;

}

