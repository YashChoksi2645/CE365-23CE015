#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <cctype>

using namespace std;

int tempCount = 1;

struct Quad {
    string op, arg1, arg2, result;
};

vector<Quad> quads;
map<string, double> varValues; // Stores values of variables/temps

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string newTemp() {
    return "t" + to_string(tempCount++);
}

// Helper to convert string (number or variable) to double
double getValue(string s) {
    try {
        return stod(s);
    } catch (...) {
        return varValues[s]; 
    }
}

void process(stack<string> &values, stack<char> &ops) {
    if (values.size() < 2) return;

    string rightStr = values.top(); values.pop();
    string leftStr = values.top(); values.pop();
    char op = ops.top(); ops.pop();

    double v1 = getValue(leftStr);
    double v2 = getValue(rightStr);
    double res = 0;

    if (op == '+') res = v1 + v2;
    else if (op == '-') res = v1 - v2;
    else if (op == '*') res = v1 * v2;
    else if (op == '/') res = (v2 != 0) ? v1 / v2 : 0;

    string temp = newTemp();
    quads.push_back({string(1, op), leftStr, rightStr, temp});
    
    varValues[temp] = res; // Store the math result
    values.push(temp);
}

void generateQuadruples(string expr) {
    stack<string> values;
    stack<char> ops;

    for (int i = 0; i < expr.length(); i++) {
        if (isspace(expr[i])) continue;

        if (isdigit(expr[i])) {
            string num = "";
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) {
                num += expr[i++];
            }
            i--;
            values.push(num);
        }
        else if (expr[i] == '(') {
            ops.push(expr[i]);
        }
        else if (expr[i] == ')') {
            while (!ops.empty() && ops.top() != '(') process(values, ops);
            if (!ops.empty()) ops.pop();
        }
        else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expr[i])) {
                process(values, ops);
            }
            ops.push(expr[i]);
        }
    }
    while (!ops.empty()) process(values, ops);
}

void printTable() {
    cout << "\nOperator\tArg 1\tArg 2\tResult" << endl;
    for (auto &q : quads) {
        cout << q.op << "\t\t" << q.arg1 << "\t" << q.arg2 << "\t" << q.result << endl;
    }
}

int main() {
    string expr;
    cout << "Enter expression (numbers only for calculation): ";
    getline(cin, expr);

    generateQuadruples(expr);
    printTable();

    if (!quads.empty()) {
        string finalTemp = quads.back().result;
        cout << "\nFinal Mathematical Result: " << varValues[finalTemp] << endl;
    }

    printf("\n23CE015\n");
    return 0;
}