#include <iostream>
#include <string>
using namespace std;

int main() {
    int numSymbols;
    cout << "Number of input symbols: ";
    cin >> numSymbols;

    char symbols[10];
    cout << "Input symbols: ";
    for (int i = 0; i < numSymbols; i++) {
        cin >> symbols[i];
    }

    int numStates;
    cout << "Enter number of states: ";
    cin >> numStates;

    int startState;
    cout << "Initial state: ";
    cin >> startState;

    int numAccept;
    cout << "Number of accepting states: ";
    cin >> numAccept;

    int acceptStates[10];
    cout << "Accepting states: ";
    for (int i = 0; i < numAccept; i++) {
        cin >> acceptStates[i];
    }

    int transition[10][10];

    cout << "Enter transition table:\n";
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < numSymbols; j++) {
            cout << "From state " << i << " on symbol " << symbols[j] << " -> ";
            cin >> transition[i][j];
        }
    }

    string input;
    cout << "Input string: ";
    cin >> input;

    int currentState = startState;

    for (int i = 0; i < input.length(); i++) {
        char c = input[i];
        int symbolIndex = -1;

        for (int j = 0; j < numSymbols; j++) {
            if (symbols[j] == c) {
                symbolIndex = j;
                break;
            }
        }

        if (symbolIndex == -1) {
            cout << "Invalid String\n";
            return 0;
        }

        currentState = transition[currentState][symbolIndex];
    }

    for (int i = 0; i < numAccept; i++) {
        if (currentState == acceptStates[i]) {
            cout << "Valid String\n";
            return 0;
        }
    }

    cout << "Invalid String\n";
    return 0;
}
