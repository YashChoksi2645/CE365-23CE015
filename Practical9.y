%{
#include <iostream>
using namespace std;

int yylex();
void yyerror(const char *s);
%}

%%

S  : 'i' E 't' S Sdash
   | 'a'
   ;

Sdash : 'e' S
      | /* empty */
      ;

E  : 'b'
   ;

%%

int main() {
    cout << "Enter string: ";
    if (yyparse() == 0)
        cout << "Valid string\n";
    else
        cout << "Invalid string\n";
    return 0;
}

void yyerror(const char *s) {
    // do nothing (handled in main)
}