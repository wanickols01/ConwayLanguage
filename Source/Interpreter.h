#pragma once

#include "Node.h"

class Number;
class Grid;
class Context;

class Interpreter
{
public:

	//Constructor
	Interpreter(std::shared_ptr<Context> context);

	//Functions
	Number visit(std::shared_ptr<Node> node);

	void setMaxWhileSize(const int size);

private:
	//variables
	std::shared_ptr<Context> context;

	int maxWhileSize;

	//Visit Functions
	Number visit(NumberNode& numberNode);
	Number visit(StringNode& numberNode);
	Number visit(UnaryOpNode& binOpNode);
	Number visit(BinOpNode& binOpNode);
	Number visit(VarAccessNode& binOpNode);
	Number visit(VarAssignNode& binOpNode);
	Number visit(ListNode& listNode);
	Number visit(IfNode& ifNode);
	Number visit(ForNode& ForNode);
	Number visit(WhileNode& WhileNode);
	Number visit(FuncNode& FuncNode);
	std::shared_ptr<Grid> findGrid(FuncNode& FuncNode);
	Number visit(MakeAlive& MakeAliveNode);

	//ErrorHandling
	Number VarNotDefined(VarAccessNode& node);
	Number no_visit_method(std::shared_ptr<Node> node);
	Number throwError(std::string details);
};

