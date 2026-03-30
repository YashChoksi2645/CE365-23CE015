#include <bits/stdc++.h>
using namespace std;

int tempCount = 1;

// Check operator precedence
int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Generate new temporary variable
string newTemp()
{
    return "t" + to_string(tempCount++);
}

// Quadruple structure
struct Quad
{
    string op, arg1, arg2, result;
};

vector<Quad> quads;

// Apply operator and generate quadruple
void process(stack<string> &values, stack<char> &ops)
{
    string right = values.top();
    values.pop();
    string left = values.top();
    values.pop();
    char op = ops.top();
    ops.pop();

    string temp = newTemp();
    quads.push_back({string(1, op), left, right, temp});

    values.push(temp);
}

// Convert expression to quadruples
void generateQuadruples(string expr)
{
    stack<string> values;
    stack<char> ops;

    for (int i = 0; i < expr.length(); i++)
    {

        // Skip spaces
        if (expr[i] == ' ')
            continue;

        // If digit (handle multi-digit numbers)
        if (isdigit(expr[i]))
        {
            string num = "";
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.'))
            {
                num += expr[i];
                i++;
            }
            i--; // adjust index
            values.push(num);
        }

        // Opening bracket
        else if (expr[i] == '(')
        {
            ops.push(expr[i]);
        }

        // Closing bracket
        else if (expr[i] == ')')
        {
            while (!ops.empty() && ops.top() != '(')
            {
                process(values, ops);
            }
            ops.pop(); // remove '('
        }

        // Operator
        else
        {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expr[i]))
            {
                process(values, ops);
            }
            ops.push(expr[i]);
        }
    }

    // Remaining operators
    while (!ops.empty())
    {
        process(values, ops);
    }
}

// Print Quadruple Table
void printQuadruples()
{
    cout << "\nOperator\tOperand1\tOperand2\tResult\n";
    for (auto &q : quads)
    {
        cout << q.op << "\t\t" << q.arg1 << "\t\t" << q.arg2 << "\t\t" << q.result << "\n";
    }
}

int main()
{
    string expr;

    cout << "Enter expression: ";
    getline(cin, expr);

    generateQuadruples(expr);
    printQuadruples();
    printf("\n23CE015");
    return 0;
}