#include <iostream>
#include <string>
using namespace std;

int main() {
    string input;
    getline(cin, input);   // read full line input

    int i = 0;
    int n = input.length();

    // Match a*
    while (i < n && input[i] == 'a') {
        i++;
    }

    // After a*, exactly "bb" must remain
    if (i + 2 == n && input[i] == 'b' && input[i + 1] == 'b') {
        cout << "Valid string";
    } else {
        cout << "Invalid string";
    }

    return 0;
}
