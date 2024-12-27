#pragma once
#include<iostream>
#include<string>
using std::string;
using std::cout;

class token {
private:
	string type;
	string lexem;
public:
	token() : type(""), lexem("") {}
	token(const string& type, const string& lexem) : type(type), lexem(lexem) {}
	~token() = default;
	string getType() const;
	string getLexem() const;
	static token makeToken(const int& condition, const string& lexem);

};
bool operator== (const token& token1, const token& token2);
bool operator!=(const token& token1, const token& token2);