#include <iostream>
#include <stack>
#include <cmath>
using namespace std;

// Precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

// Apply operation
double applyOp(double a, double b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : throw runtime_error("Divide by zero");
        case '^': return pow(a, b);
    }
    return 0;
}

// Evaluate expression
double evaluate(string expr) {
    stack<double> values;
    stack<char> ops;

    for (int i = 0; i < expr.length(); i++) {

        if (expr[i] == ' ') continue;

        // Number
        if (isdigit(expr[i])) {
            double val = 0;
            while (i < expr.length() && isdigit(expr[i])) {
                val = val * 10 + (expr[i] - '0');
                i++;
            }
            i--;
            values.push(val);
        }

        // '('
        else if (expr[i] == '(') {
            ops.push(expr[i]);
        }

        // ')'
        else if (expr[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(a, b, op));
            }
            ops.pop(); // remove '('
        }

        // Operator
        else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expr[i])) {
                double b = values.top(); values.pop();
                double a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(a, b, op));
            }
            ops.push(expr[i]);
        }
    }

    while (!ops.empty()) {
        double b = values.top(); values.pop();
        double a = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(a, b, op));
    }

    return values.top();
}

int main() {
    string expr;
    cout << "Enter expression: ";
    getline(cin, expr);

    try {
        double result = evaluate(expr);
        cout << "Result = " << result << endl;
    } catch (...) {
        cout << "Invalid expression\n";
    }

    return 0;
}