#include <iostream>
#include <fstream>
#include "token.h"
#include "Parser.h"
#include "Node.h"
#include "hashTable.h"
#include "lexicalAnalyzator.h"

int main() {
	std::ifstream fin;
	std::ofstream fout;
	fin.open("input.txt");
	fout.open("output.txt");
	LexAnalyzator lex;
	vector<token> vectorOfTokens;
	string lexem = LexAnalyzator::getLexem(fin);
	hashTable table;
	bool f = 0;
	while (lexem != "1e") {
		int condition = lex.getCondition(lexem);
		if (condition == -1) {
			f = 1;
			fout << lexem << ' ' << "ERROR\n";
		}
		else {
			token newToken = token::makeToken(condition, lexem);
			table.addToken(newToken);
			vectorOfTokens.push_back(newToken);
		}
		lexem = LexAnalyzator::getLexem(fin);
	}
	table.printTable(fout);
	if (f) {
		cout << "BAD LEXEM\n";
		return 0;
	}
	Parser parse(vectorOfTokens);
	Node root = parse.parse();
	root.printRoot(0);
	fin.close();
	fout.close();
	return 0;
}
