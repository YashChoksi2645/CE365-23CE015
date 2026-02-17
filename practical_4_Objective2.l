%{
#include <stdio.h>
%}

%%
"charusat"  { printf("university"); }
\n          { printf("%s", yytext); return 0; } 
.           { printf("%s", yytext); }
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter the text: ");
    yylex();
    printf("23ce098");
    return 0;
}