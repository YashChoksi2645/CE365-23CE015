#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <stack>
using namespace std;

map<char, vector<string>> grammar;
map<char, set<char>> FIRST, FOLLOW;
map<pair<char, char>, string> table;

set<char> nonTerminals, terminals;
char startSymbol;

// Find FIRST
set<char> findFirst(char c) {
    if (!isupper(c)) return {c};

    if (!FIRST[c].empty()) return FIRST[c];

    for (auto prod : grammar[c]) {
        for (int i = 0; i < prod.size(); i++) {
            set<char> temp = findFirst(prod[i]);
            for (char t : temp) {
                if (t != '#') FIRST[c].insert(t);
            }
            if (temp.find('#') == temp.end()) break;
            if (i == prod.size() - 1) FIRST[c].insert('#');
        }
    }
    return FIRST[c];
}

// Find FOLLOW
void findFollow(char c) {
    if (c == startSymbol) FOLLOW[c].insert('$');

    for (auto g : grammar) {
        for (auto prod : g.second) {
            for (int i = 0; i < prod.size(); i++) {
                if (prod[i] == c) {
                    if (i + 1 < prod.size()) {
                        set<char> temp = findFirst(prod[i + 1]);
                        for (char t : temp) {
                            if (t != '#') FOLLOW[c].insert(t);
                        }
                        if (temp.find('#') != temp.end()) {
                            for (char t : FOLLOW[g.first]) {
                                FOLLOW[c].insert(t);
                            }
                        }
                    } else {
                        if (c != g.first) {
                            for (char t : FOLLOW[g.first]) {
                                FOLLOW[c].insert(t);
                            }
                        }
                    }
                }
            }
        }
    }
}

// Build Parsing Table
bool buildTable() {
    bool isLL1 = true;

    for (auto g : grammar) {
        char A = g.first;
        for (auto prod : g.second) {
            set<char> firstSet;

            if (prod == "#") firstSet.insert('#');
            else firstSet = findFirst(prod[0]);

            for (char t : firstSet) {
                if (t != '#') {
                    if (table[{A, t}] != "") isLL1 = false;
                    table[{A, t}] = prod;
                }
            }

            if (firstSet.find('#') != firstSet.end()) {
                for (char t : FOLLOW[A]) {
                    if (table[{A, t}] != "") isLL1 = false;
                    table[{A, t}] = prod;
                }
            }
        }
    }
    return isLL1;
}

// Validate string
bool validate(string input) {
    stack<char> st;
    st.push('$');
    st.push(startSymbol);
    input += '$';

    int i = 0;

    while (!st.empty()) {
        char top = st.top();
        st.pop();

        if (top == input[i]) {
            i++;
        } else if (!isupper(top)) {
            return false;
        } else {
            string prod = table[{top, input[i]}];
            if (prod == "") return false;

            if (prod != "#") {
                for (int j = prod.size() - 1; j >= 0; j--) {
                    st.push(prod[j]);
                }
            }
        }
    }

    return true;
}

int main() {
    int n;
    cout << "Enter number of productions: ";
    cin >> n;

    cout << "Enter productions (e.g., E=TR|#):\n";

    for (int i = 0; i < n; i++) {
        string prod;
        cin >> prod;

        char lhs = prod[0];
        nonTerminals.insert(lhs);

        if (i == 0) startSymbol = lhs;

        for (int j = 2; j < prod.size(); j++) {
            string rhs = "";
            while (j < prod.size() && prod[j] != '|') {
                rhs += prod[j++];
            }
            grammar[lhs].push_back(rhs);
        }
    }

    // Identify terminals
    for (auto g : grammar) {
        for (auto prod : g.second) {
            for (char c : prod) {
                if (!isupper(c) && c != '#') terminals.insert(c);
            }
        }
    }

    // Compute FIRST
    for (auto nt : nonTerminals) findFirst(nt);

    // Compute FOLLOW
    for (auto nt : nonTerminals) findFollow(nt);

    // Build table
    bool isLL1 = buildTable();

    cout << "\nParsing Table:\n";
    for (auto nt : nonTerminals) {
        for (auto t : terminals) {
            if (table[{nt, t}] != "") {
                cout << nt << "," << t << " -> " << table[{nt, t}] << endl;
            }
        }
        if (table[{nt, '$'}] != "") {
            cout << nt << ",$ -> " << table[{nt, '$'}] << endl;
        }
    }

    if (isLL1)
        cout << "\nGrammar is LL(1)\n";
    else
        cout << "\nGrammar is NOT LL(1)\n";

    string input;
    cout << "\nEnter string to validate: ";
    cin >> input;

    if (validate(input))
        cout << "Valid string\n";
    else
        cout << "Invalid string\n";

    return 0;
}