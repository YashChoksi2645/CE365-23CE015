#include <iostream>
#include <string>
using namespace std;

int main() {
    string input;
    cout << "Enter input string: ";
    cin >> input;

    // DFA states
    // 0 -> Start state
    // 1 -> Valid state
    // 2 -> Dead state
    int currentState = 0;

    for (int i = 0; i < input.length(); i++) {
        char c = input[i];

        if (currentState == 0) {
            // First character must be lowercase alphabet
            if (c >= 'a' && c <= 'z') {
                currentState = 1;
            } else {
                currentState = 2;
            }
        }
        else if (currentState == 1) {
            // After first char, alphabets and digits allowed
            if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
                currentState = 1;
            } else {
                currentState = 2;
            }
        }
        else {
            // Dead state
            currentState = 2;
        }
    }

    // Accepting state is 1
    if (currentState == 1) {
        cout << "Valid String\n";
    } else {
        cout << "Invalid String\n";
    }

    return 0;
}
