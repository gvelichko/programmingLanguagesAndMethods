#include "token.h"

bool operator==(const token& token1, const token& token2) {
	if (token1.getType() == token2.getType() && token1.getLexem() == token2.getLexem()) {
		return true;
	}
	return false;
}

bool operator!=(const token& token1, const token& token2) {
	return !(token1 == token2);
}

string token::getType() const {
	return this->type;
}

string token::getLexem() const {
	return this->lexem;
}

token token::makeToken(const int& condition, const string& lexem){
	if (condition == 9 || condition == 10 || condition == 23) {
		return token("int_num", lexem);
	}
	else if (condition == 11 || condition == 14) {
		return token("separation", lexem);
	}
	else if (condition == 12 || condition == 13 || condition == 22) {
		return token("operator", lexem);
	}
	else if (condition == 19 || condition == 34 || condition == 26 ||  condition == 42 || condition == 29 || condition == 31 || condition == 39) {
		return token("key_word", lexem);
	}
	else {
		return token("id_name", lexem);
	}
}
