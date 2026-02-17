%{
#include <stdio.h>
int c = 0, w = 0, l = 0;
%}

%%
\n      { l++; c++; }
[ \t]+  { c += yyleng; }
[^\t\n ]+ { w++; c += yyleng; }
%%

int yywrap() { return 1; }

int main() {
    // This looks for the file in the current working directory
    FILE *f = fopen("test.txt", "r");
    if (!f) {
        printf("Could not open test.txt\n");
        return 1;
    }
    yyin = f;
    yylex();
    printf("\nCharacters : %d\nWords : %d\nLines : %d\n", c, w, l);
    fclose(f);
    printf("23ce098");
    return 0;
}