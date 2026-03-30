#include <iostream>
#include <string>
using namespace std;

string input;
int pos = 0;

// Forward declarations
bool S();
bool L();
bool Ldash();

// Function to match expected character
bool match(char expected) {
    if (pos < input.length() && input[pos] == expected) {
        pos++;
        return true;
    }
    return false;
}

// S → ( L ) | a
bool S() {
    if (match('a')) {
        return true;
    }
    else if (match('(')) {
        if (L()) {
            if (match(')')) {
                return true;
            }
        }
        return false;
    }
    return false;
}

// L → S L'
bool L() {
    if (S()) {
        return Ldash();
    }
    return false;
}

// L' → , S L' | ε
bool Ldash() {
    if (match(',')) {
        if (S()) {
            return Ldash();
        }
        return false;
    }
    return true; // ε (empty)
}

int main() {
    while (true) {
        pos = 0; // Reset position for each iteration
        
        cout << "\nEnter input string (or type 'exit' to quit): ";
        cin >> input;
        
        // Check if user wants to exit
        if (input == "exit") {
            cout << "Exiting program..." << endl;
            break;
        }
        
        if (S() && pos == input.length()) {
            cout << "Valid string" << endl;
        } else {
            cout << "Invalid string" << endl;
        }
    }

    return 0;
}