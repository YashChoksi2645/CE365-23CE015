%{
#include <stdio.h>
int line_no = 1;
%}

%option noyywrap

/* Definitions for clarity */
DIGIT       [0-9]
LETTER      [a-zA-Z_]
ID          {LETTER}({LETTER}|{DIGIT})*
ERROR_ID    {DIGIT}+{LETTER}+
WS          [ \t]+

%%

\n          { line_no++; }
{WS}        { /* Skip whitespace */ }

"//".* { /* Skip Single Line Comment */ }
"/*"([^*]|\*+[^*/])*\*+"/"   { /* Skip Multi-line Comment */ }

"int"|"float"|"char"|"void"|"return"|"struct"|"long"|"scanf"|"printf" {
    printf("Keyword: %s\n", yytext);
}

{ERROR_ID} { 
    printf("\nLEXICAL ERROR\nLine %d : %s invalid lexeme\n\n", line_no, yytext); 
}

{ID} { 
    printf("Identifier: %s\n", yytext); 
}

{DIGIT}+("."{DIGIT}+)? { printf("Constant: %s\n", yytext); }
"'"."'"                { printf("Constant: %s\n", yytext); }
\"[^\"]*\"             { printf("String: %s\n", yytext); }

"=="|"<="|">="|"="|"+"|"-"|"*"|"/"|"&" { printf("Operator: %s\n", yytext); }

"("|")"|"{"|"}"|";"|","|"."             { printf("Punctuation: %s\n", yytext); }

.           { /* Ignore other characters */ }

%%

int main() {
    yyin = fopen("input.txt", "r");
    if(!yyin) {
        printf("Missing input.txt file!\n");
        return 1;
    }
    printf("--- TOKENS ---\n");
    yylex();
    return 0;
}