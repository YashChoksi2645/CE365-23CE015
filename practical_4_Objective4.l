%{
#include <stdio.h>

int lower = 0;
int upper = 0;
int digit = 0;
int special = 0;
int total = 0;
%}

%%

[a-z]       { lower++; total++; }
[A-Z]       { upper++; total++; }
[0-9]       { digit++; total++; }
[*;#$@]     { special++; total++; }
\n          {
                if (total >= 9 && total <= 15 && lower >= 1 && upper >= 1 && digit >= 1 && special >= 1) {
                    printf("Valid password\n");
                } else {
                    printf("Invalid password\n");
                }
                // Reset counters for the next input
                lower = upper = digit = special = total = 0;
            }
.           { total++; } // Count any other character but it won't satisfy specific category rules

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter password to validate: \n");
    yylex();
    return 0;
}