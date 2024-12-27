#include "Parser.h"
#include <algorithm>

bool Parser::isCONST(const string& s) {
	bool f = 1;
	for (auto i : s) {
		if (!(i >= '0' && i <= '9')) {
			f = 0;
		}
	}
	return f;
}
bool Parser::isID(const string& s) {
	if (vt[i - 1].getType() == "id_name") {
		return true;
	}
	return false;
}

void Parser::getLexem() {
	if (i >= vt.size()) {
		lexem = '#';
		return;
	}
	lexem = vt[i].getLexem();
	++i;
}

void Parser::printReversePolishWrite(string& reversePolishWrite){
	cout << reversePolishWrite << '\n';
}

bool Parser::checkVars() {
	if (vt[i].getLexem() == "," || vt[i].getLexem() == ":") return true;
	else return false;
}

void printError(string Error) {
	cout << Error << '\n';
	exit(0);
}


void Parser::Procedure(Node& n) {
	if (lexem == "procedure") {
		// Procedure → Begin Descriptions Operators End
		n.addSon("Begin");
		Begin(n.getSon(0));
		n.reversePolishWrite = n.getSon(0).reversePolishWrite + '\n';
		n.addSon("Descriptions");
		Descriptions(n.getSon(1));
		n.reversePolishWrite += n.getSon(1).reversePolishWrite + '\n';
		isOpers = 1;
		n.addSon("Operators");
		Operators(n.getSon(2));
		n.reversePolishWrite += n.getSon(2).reversePolishWrite + '\n';
		n.addSon("End");
		End(n.getSon(3));
		n.reversePolishWrite += n.getSon(3).reversePolishWrite;
		printReversePolishWrite(n.reversePolishWrite);

	}
	else printError("Syntax Error! It is expected here 'procedure'");
}


void Parser::Begin(Node& n) {
	if (lexem == "procedure") {
		// Begin → procedure ProcedureName ; begin
		n.addSon("procedure");
		getLexem();
		n.addSon("ProcedureName");
		ProcedureName(n.getSon(1));
		n.reversePolishWrite = "procedure " + n.getSon(1).reversePolishWrite;
		if (lexem == ";") {
			n.addSon(";");
			getLexem();
		}
		else {
			printError("Syntax Error! It is expected here ';'");
		}
		if (lexem == "begin") {
			n.addSon("begin");
			n.reversePolishWrite += " begin";
			getLexem();
		}
		else {
			printError("Syntax Error! It is expected here 'begin'");
		}
		n.reversePolishWrite += " 3 DECL ";
	}
	else printError("Syntax Error! It is expected here 'procedure'");
}

void Parser::End(Node& n) {
	if (lexem == "end") {
		// End → end
		n.addSon("end");
		n.reversePolishWrite = lexem;
		getLexem();
	}
	else printError("Syntax Error! It is expected here 'end'");
}

void Parser::ProcedureName(Node& n) {
	if (isID(lexem)) {
		// ProcedureName → Id
		n.addSon(lexem);
		n.reversePolishWrite = lexem;
		getLexem();
	}
	else {
		printError("Syntax Error! It is expected here 'procedure_name'");
	}
}

void Parser::Descriptions(Node& n) {
	if (lexem == "var") {
		// Descriptions → var DescrList
		n.addSon("var");
		getLexem();
		n.addSon("DescrList");
		DescrList(n.getSon(1));
		n.reversePolishWrite = "var ";
		n.reversePolishWrite += n.getSon(1).reversePolishWrite + ' ';
		n.reversePolishWrite += to_string(n.getSon(1).lvl + 1);
		n.reversePolishWrite += " DECL";
	}
	else {
		printError("Syntax Error! It is expected here 'var'");
	}
}

void Parser::DescrList(Node& n) {
	if (isID(lexem)) {
		// DescrList → Descr DescrList’
		n.addSon("Descr");
		Descr(n.getSon(0));
		n.addSon("DescrList1");
		DescrList1(n.getSon(1));
		n.lvl = 1 + n.getSon(1).lvl;
		n.reversePolishWrite = n.getSon(0).reversePolishWrite + ' ' + n.getSon(1).reversePolishWrite;
	}
	else printError("Syntax Error! It is expected here 'id_name'");
}

void Parser::DescrList1(Node& n) {
	if (lexem == "case") {
		// DescrList’→eps
		n.addSon("eps");
	}
	else if (isID(lexem)) {
		if (checkVars()) {
			// DescrList’→DescrList
			n.addSon("DescrList");
			DescrList(n.getSon(0));
			n.lvl = n.getSon(0).lvl;
			n.reversePolishWrite += n.getSon(0).reversePolishWrite;
		}
		else {
			//DescrList’→ eps
			n.addSon("eps");
		}
	}
	else {
		//DescrList’→ eps
		n.addSon("eps");
	}
}

void Parser::Descr(Node& n) {
	if (isID(lexem)) {
		// Descr → VarList : Type ;
		n.addSon("VarList");
		VarList(n.getSon(0));
		if (lexem == ":") {
			n.addSon(":");
			getLexem();
		}
		else {
			printError("Syntax Error! It is expected here ':'");
		}
		n.addSon("Type");
		Type(n.getSon(2));
		if (lexem == ";") {
			n.addSon(";");
			getLexem();
		}
		else {
			printError("Syntax Error! It is expected here ';'");
		}
		n.reversePolishWrite = n.getSon(2).reversePolishWrite + ' ' + n.getSon(0).reversePolishWrite + ' ' + to_string(n.getSon(0).lvl + 1) + " DECL";
	}
	else printError("Syntax Error! It is expected here 'id_name'");
}

void Parser::VarList(Node& n) {
	if (isID(lexem)) {
		// VarList→ Id VarList’
		n.addSon("Id");
		Id(n.getSon(0));
		n.addSon("VarList1");
		VarList1(n.getSon(1));
		n.lvl = n.getSon(1).lvl + 1;
		n.reversePolishWrite = n.getSon(0).reversePolishWrite + ' ' + n.getSon(1).reversePolishWrite;
	}
	else printError("Syntax Error! It is expected here 'id_name'");
}

void Parser::VarList1(Node& n) {
	if (lexem == ":") {
		// VarList’→ eps
		n.addSon("eps");
	}
	else if (lexem == ",") {
		// VarList’→ , VarList
		n.addSon(",");
		getLexem();
		n.addSon("VarList");
		VarList(n.getSon(1));
		n.lvl = n.getSon(1).lvl;
		n.reversePolishWrite = n.getSon(1).reversePolishWrite;
	}
	else printError("Syntax Error! It is expected here ':' or ','");
}

void Parser::Type(Node& n) {
	if (lexem == "integer") {
		// Type → integer
		n.addSon("integer");
		n.reversePolishWrite = lexem;
		getLexem();
	}
	else printError("Syntax Error! It is expected here 'integer'");
}

void Parser::Operators(Node& n) {
	if (lexem == "case" || isID(lexem)) {
		// Operators → Op Operators’
		n.addSon("Op");
		Op(n.getSon(0));
		n.addSon("Operators1");
		Operators1(n.getSon(1));
		n.reversePolishWrite = n.getSon(0).reversePolishWrite + ' ' + n.getSon(1).reversePolishWrite;
	}
	else printError("Syntax Error! It is expected here 'case' or 'id_name'");
}

void Parser::Operators1(Node& n) {
	if (lexem == "case" || isID(lexem)) {
		// Operators’→Operators
		n.addSon("Operators");
		Operators(n.getSon(0));
		n.reversePolishWrite = n.getSon(0).reversePolishWrite;
	}
	else if (lexem == "end" || isCONST(lexem)) {
		// Operators’→eps
		n.addSon("eps");
	}
	else printError("Syntax Error! It is expected here 'case' or 'end' or 'id_name' or 'int_num'");
}



void Parser::Op(Node& n) {
	if (lexem == "case") {
		// Op → case Expr of Options end ;
		n.addSon("case");
		getLexem();
		n.addSon("Expr");
		Expr(n.getSon(1));
		if (lexem == "of") {
			n.addSon("of");
			getLexem();
		}
		else {
			printError("Syntax Error! It is expected here 'of'");
		}
		n.addSon("Options");
		++mcount;
		int tmp = mcount;
		Options(n.getSon(3), n.getSon(1), " m" + to_string(mcount) + " BRL ");
		n.reversePolishWrite = n.getSon(3).reversePolishWrite;
		n.reversePolishWrite += " m" + to_string(tmp) + " DEFL";
		if (lexem == "end") {
			n.addSon("end");
			getLexem();
		}
		else {
			printError("Syntax Error! It is expected here 'end'");
		}
		if (lexem == ";") {
			n.addSon(";");
			getLexem();
		}
		else {
			printError("Syntax Error! It is expected here ';'");
		}
	}
	else if (isID(lexem)) {
		// Op → Id := Expr ;
		n.addSon("Id");
		Id(n.getSon(0));
		if (lexem == ":=") {
			n.addSon(":=");
			getLexem();
		}
		else {
			printError("Syntax Error! It is expected here ':='");
		}
		n.addSon("Expr");
		Expr(n.getSon(2));
		if (lexem == ";") {
			n.addSon(";");
			getLexem();
		}
		else {
			printError("Syntax Error! It is expected here ';'");
		}
		n.reversePolishWrite = n.getSon(0).reversePolishWrite + ' ' + n.getSon(2).reversePolishWrite + " :=";
	}
	else printError("Syntax Error! It is expected here 'case' or 'end' or 'id_name' or 'int_num'");
}

void Parser::Options(Node& n, Node& n2, string s) {
	if (isCONST(lexem)) {
		// Options→ Const : Operators Options’
		n.addSon("Const");
		Const(n.getSon(0));
		if (lexem == ":") {
			n.addSon(":");
			getLexem();
		}
		else {
			printError("Syntax Error! It is expected here ':'");
		}
		n.addSon("Operators");
		Operators(n.getSon(2));
		n.addSon("Options1");
		Options1(n.getSon(3), n2, s);
		++mcount;
		n.reversePolishWrite = n2.reversePolishWrite + ' ' + n.getSon(0).reversePolishWrite + " ==" + " m" + to_string(mcount) + " BF " + n.getSon(2).reversePolishWrite + s + " m" + to_string(mcount) + " DEFL" + ' ' + n.getSon(3).reversePolishWrite;
	}
	else printError("Syntax Error! It is expected here 'int_num'");
}


void Parser::Options1(Node& n, Node& n2, string s) {
	if (isCONST(lexem)) {
		// Options’ → Options
		n.addSon("Options");
		Options(n.getSon(0), n2, s);
		n.reversePolishWrite += n.getSon(0).reversePolishWrite;
	}
	else if (lexem == "end") {
		// Options’→eps
		n.addSon("eps");
	}
	else printError("Syntax Error! It is expected here 'end' or 'int_num'");
}

void Parser::Expr(Node& n) {
	if (lexem == "(" || isID(lexem) || isCONST(lexem)) {
		// Expr → SimpleExpr Expr’
		n.addSon("SimpleExpr");
		SimpleExpr(n.getSon(0));
		n.addSon("Expr1");
		Expr1(n.getSon(1));
		n.reversePolishWrite += n.getSon(0).reversePolishWrite + ' ' + n.getSon(1).reversePolishWrite;
	}
	else printError("Syntax Error! It is expected here '(' or 'int_num' or 'id_name");
}

void Parser::Expr1(Node& n) {
	if (lexem == ";" || lexem == ")" || lexem == "of") {
		// Expr’->eps
		n.addSon("eps");
	}
	else if (lexem == "+") {
		// Expr' -> +Expr
		n.addSon("+");
		getLexem();
		n.addSon("Expr");
		Expr(n.getSon(1));
		n.reversePolishWrite += n.getSon(1).reversePolishWrite + '+';
	}
	else if (lexem == "-") {
		// Expr' -> -Expr
		n.addSon("-");
		getLexem();
		n.addSon("Expr");
		Expr(n.getSon(1));
		n.reversePolishWrite += n.getSon(1).reversePolishWrite + '-';
	}
	else printError("Syntax Error! It is expected here '+' or '-' or ';' or ')' or 'of'");
}

void Parser::SimpleExpr(Node& n) {
	if (lexem == "(") {
		// SimpleExpr → ( Expr )
		n.addSon("(");
		getLexem();
		n.addSon("Expr");
		Expr(n.getSon(1));
		if (lexem == ")") {
			n.addSon(")");
			getLexem();
		}
		else {
			printError("Syntax Error! It is expected here ')'");
		}
		n.reversePolishWrite = n.getSon(1).reversePolishWrite;
	}
	else if (isID(lexem)) {
		// SimpleExpr → Id
		n.addSon("Id");
		Id(n.getSon(0));
		n.reversePolishWrite = n.getSon(0).reversePolishWrite;
	}
	else if (isCONST(lexem)) {
		// SimpleExpr → Const
		n.addSon("Const");
		Const(n.getSon(0));
		n.reversePolishWrite = n.getSon(0).reversePolishWrite;
	}
	else printError("Syntax Error! It is expected here '(' or 'id_name' or 'int_num'");
}

void Parser::Id(Node& n) {
	if (isID(lexem)) {
		// Id → id_name
		n.addSon(lexem);
		n.reversePolishWrite = lexem;
		if (!isOpers) {
			if (UsedVars.count(lexem) == 0) {
				UsedVars.insert(lexem);
			}
			else {
				cout << lexem + " has already declared\n";
			}
		}
		else {
			if (UsedVars.count(lexem) == 0) {
				cout << lexem + " has NOT declared\n";
			}

		}
		getLexem();
	}
	else printError("Syntax Error! It is expected here 'id_name'");
}

void Parser::Const(Node& n) {
	if (isCONST(lexem)) {
		// Const → int_num
		n.addSon(lexem);
		n.reversePolishWrite = lexem;
		getLexem();
	}
	else printError("Syntax Error! It is expected here 'int_num'");
}


Parser::Parser(std::vector<token> VT) {
	vt = VT;
	i = 0;
}

Node Parser::parse() {
	Node root("Procedure");
	getLexem();
	Procedure(root);
	return root;
}
