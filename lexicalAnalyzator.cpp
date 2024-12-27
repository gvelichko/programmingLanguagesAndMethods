#include "lexicalAnalyzator.h"


string LexAnalyzator::getLexem(std::ifstream& fin) {
    string lexem = "";
    char c = fin.get();
	while (c != '\n' && c != ' ' && c != EOF) {
        lexem += c;
        c = fin.get();
    }
	if (c == EOF && lexem.size() == 0) {
		return string("1e");
	}
	return lexem;
}

int LexAnalyzator::getCondition(const string& lexem){
    int resultCondition = 0;
	for (int i = 0; i < lexem.size(); ++i) {
		int j = 0;
		while (j < alphabet.size() && alphabet[j] != lexem[i]) {
			++j;
		}
		if (j == alphabet.size() || transitFunction[resultCondition][j] == -1) {
			return -1;
		}
		resultCondition = transitFunction[resultCondition][j];
	}
	return resultCondition;
}
