#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using std::vector;
using std::string;
using std::cout;
using std::cin;
class Node {
private:
	string data;
	vector<Node> children;
public:
	int lvl = 0;
	string reversePolishWrite;
	Node(string s);
	void addSon(string s);
	Node& getSon(int i);
	void printRoot(int lvl);
};

