#include <stdio.h>

int main() {
    int a = 5, b = 10;
    char ch = 'x';
    float num = 25.4;

    // This is a single-line comment
    a = a + b;
    // multi comment start 
    /* This is a
       multi-line comment */
    // multi comment end
    printf("Sum is: %d", a);

    int 9Z = 100;     // invalid identifier
    b = @ + 3 + #;        // invalid symbol
    int valid_name = 20;

    return 0;
}
