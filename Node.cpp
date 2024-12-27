#include "Node.h"

Node::Node(string s){
	data = s;
}

void Node::addSon(string s){
	Node n(s);
	children.push_back(n);
}

Node& Node::getSon(int i){
	return children[i];
}

void Node::printRoot(int lvl){
	for (int i = 0; i < lvl; ++i) {
		cout << "  ";
	}
	cout << data << '\n';
	for (Node n : children) {
		n.printRoot(lvl + 1);
	}
}
