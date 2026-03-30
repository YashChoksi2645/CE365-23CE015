#include <iostream>
#include <set>
#include <map>
using namespace std;

// FIRST and FOLLOW sets
map<char, set<char>> firstSet;
map<char, set<char>> followSet;

// Grammar symbols
set<char> nonTerminals = {'S','A','B','C','D'};

// Function to compute FIRST sets manually as per grammar
void computeFirst() {
    firstSet['A'] = {'a', '#'};       // # represents ε
    firstSet['B'] = {'b', '#'};
    firstSet['C'] = {'(', 'c'};

    // FIRST(D) = FIRST(A C)
    firstSet['D'].insert('a');
    firstSet['D'].insert('(');
    firstSet['D'].insert('c');

    // FIRST(S) = FIRST(A B C) U FIRST(D)
    firstSet['S'].insert('a');
    firstSet['S'].insert('b');
    firstSet['S'].insert('(');
    firstSet['S'].insert('c');
}

// Function to compute FOLLOW sets manually
void computeFollow() {
    followSet['S'] = {')', '$'};
    followSet['A'] = {'b', '(', 'c'};
    followSet['B'] = {'a', '(', 'c'};
    followSet['C'] = {')', '$'};
    followSet['D'] = {')', '$'};
}

void printSets() {
    // Print FIRST sets in specific order
    char order[] = {'S', 'A', 'B', 'C', 'D'};
    
    for(int i = 0; i < 5; i++) {
        char nt = order[i];
        cout << "First(" << nt << ") = {";
        bool first = true;
        for(auto ch : firstSet[nt]) {
            if(!first) cout << ",";
            cout << " ";
            if(ch == '#')
                cout << "ε";
            else
                cout << ch;
            first = false;
        }
        cout << "}\n";
    }
    
    for(int i = 0; i < 5; i++) {
        char nt = order[i];
        cout << "Follow(" << nt << ") = {";
        bool first = true;
        for(auto ch : followSet[nt]) {
            if(!first) cout << ",";
            cout << " ";
            cout << ch;
            first = false;
        }
        cout << "}\n";
    }
}

int main() {
    computeFirst();
    computeFollow();
    printSets();
    return 0;
}