#pragma once

#include "Token.h"

class Case;

const enum nodeTypes
{
	NT_NumberNode = 0,
	NT_StringNode,
	NT_BinOpNode,
	NT_UnaryOpNode,
	NT_VarAssignNode,
	NT_VarAccessNode,
	NT_IfNode,
	NT_ForNode,
	NT_WhileNode,
	NT_ListNode,
	NT_FuncNode,
	NT_AliveNode,
	NT_EmptyNode
};

//Base Node
class Node
{
public:
	//Constructor
	Node(Token& tok, nodeTypes type);

	//Functions
	virtual string represent() { return "Error, base node called"; };

	//Accessors
	tokenTypes getTokenType() const;
	const nodeTypes getNodeType() const;
	const Token& getToken() const;

	const std::shared_ptr<LinePosition> getLinePosition() const;
protected:
	Token tok;
	nodeTypes type;
};

//Node Implementations
class NumberNode : public Node
{
public:
	NumberNode(Token& tok);

	string represent() override;
};

class StringNode : public Node
{
public:
	StringNode(Token& tok);

	string represent() override;
};

class BinOpNode : public Node 
{
public:
	BinOpNode(std::shared_ptr<Node> left_node, Token& op_tok, std::shared_ptr<Node> right_node);

	string represent() override;

	std::shared_ptr<Node> leftNode;
	std::shared_ptr<Node> rightNode;
};

class UnaryOpNode : public Node 
{
public:
	UnaryOpNode(Token& op_tok, std::shared_ptr<Node> other_node);

	string represent() override;

	std::shared_ptr<Node> otherNode;
};

class VarAssignNode : public Node 
{
public:
	VarAssignNode(Token& op_tok, string var_name, std::shared_ptr<Node> other_node, string var_type);

	string represent() override;

	string varName;
	string varType;
	std::shared_ptr<Node> valueNode;

};

class VarAccessNode : public Node
{
public:
	VarAccessNode(Token& op_tok);
	string represent() override;
};

class IfNode : public Node
{
public:
	IfNode(Token& op_tok, std::shared_ptr<vector<Case>> cases, std::shared_ptr<Node> else_node);
	string represent() override;

	std::shared_ptr<vector<Case>> cases;
	std::shared_ptr<Node> elseNode;
};

class ForNode : public Node
{
public:
	ForNode(Token& op_tok, string var_name, string var_type, std::shared_ptr<Node> start_node, std::shared_ptr<Node> end_node, std::shared_ptr<Node> step_node, std::shared_ptr<Node> expression);
	string represent() override;

	string varName;
	string varType;
	std::shared_ptr<Node> startNode;
	std::shared_ptr<Node> endNode;
	std::shared_ptr<Node> stepNode;  
	std::shared_ptr<Node> expression;
};

class WhileNode : public Node
{
public:
	WhileNode(Token& op_tok, std::shared_ptr<Case> passed_case);
	string represent() override;

	std::shared_ptr<Case> case_;
};

class ListNode : public Node
{
public:
	ListNode(Token& op_tok, string varname, std::shared_ptr<std::vector<std::shared_ptr<Node>>> element_nodes);
	string represent() override;

	string varName;
	std::shared_ptr<std::vector<std::shared_ptr<Node>>> elementNodes;
};

class FuncNode : public Node
{
public:
	FuncNode(Token& tok, std::shared_ptr<vector<shared_ptr<Node>>> arguments, string varname, string varType);
	string represent() override;

	std::shared_ptr<vector<shared_ptr<Node>>> arguments; //Must have at least one
	string varName;
	string varType;
};

class MakeAlive : public Node
{
public:
	MakeAlive(Token& tok, string gridname, std::shared_ptr<Node> aliveTable);
	string represent() override;

	std::shared_ptr<Node> aliveTable; //list of list of bools
	string gridName;

};


class EmptyNode : public Node
{
public:

	EmptyNode(Token& tok) : Node(tok, nodeTypes::NT_EmptyNode) {};
	string represent() override { return ""; };
};