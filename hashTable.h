#pragma once
#include<iostream>
#include<fstream>
#include"token.h"
class hashTable {
private:
	int getHash(const token& Token);
	const int size = 1e5 + 19;
	token* table = nullptr;
public:
	hashTable();
	~hashTable();
	void addToken(const token& Token);
	void printTable(std::ofstream& fout);
};