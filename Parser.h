#pragma once
#include "Node.h"
#include "token.h"
#include <iostream>
#include <string>
#include <set>
using std::set;
using std::to_string;
class Parser{
private:
	string lexem;
	vector<token> vt;
	int i;
	bool isCONST(const string& s);
	bool isID(const string& s);
	bool checkVars();
	void getLexem();
	void printReversePolishWrite(string& reversePolishWrite);

	void Procedure(Node& n);
	void Begin(Node& n);
	void End(Node& n);
	void ProcedureName(Node& n);
	void Descriptions(Node& n);
	void DescrList(Node& n);
	void DescrList1(Node& n);
	void Descr(Node& n);
	void VarList(Node& n);
	void VarList1(Node& n);
	void Type(Node& n);
	void Operators(Node& n);
	void Operators1(Node& n);
	void Op(Node& n);
	void Options(Node& n, Node& n2, string s);
	void Options1(Node& n, Node& n2, string s);
	void Expr(Node& n);
	void Expr1(Node& n);
	void SimpleExpr(Node& n);
	void Id(Node& n);
	void Const(Node& n);
	int mcount = 0;
	bool isOpers = 0;
	set<string> UsedVars;
public:
	Parser(vector<token> VT);
	Node parse();
};

