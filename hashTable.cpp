#include "hashTable.h"

int hashTable::getHash(const token& Token) {
    const int mod = 1e5 + 19;
    const int p = 259;
    int k = 1;
    int hash = 0;
    for (int i = 0; i < Token.getLexem().size(); ++i) {
        hash += Token.getLexem()[i] * k;
        hash %= mod;
        k = (k * p) % mod;
    }
    for (int i = 0; i < Token.getType().size(); ++i) {
        hash += Token.getType()[i] * k;
        hash %= mod;
        k = (k * p) % mod;
    }
    return hash;
}

hashTable::hashTable() {
    table = new token[size];
}

hashTable::~hashTable() {
    delete[] table;
}

void hashTable::addToken(const token& Token) {
    int hash = getHash(Token);
    while (table[hash].getLexem().size() > 0 && (Token != table[hash])) {
        ++hash;
        hash %= size;
    }
    if (table[hash].getLexem().size() == 0) {
        table[hash] = Token;
    }
}

void hashTable::printTable(std::ofstream& fout) {
    fout << "ID" << "  " << "Type of lexem" << "  " << "Lexem\n";
    for (int i = 0; i < size; ++i) {
        if (table[i].getLexem().size() > 0 && table[i].getType().size() > 0) {
            fout << i << ' ' << table[i].getType() << ' ' << table[i].getLexem() << '\n';
        }
    }
}