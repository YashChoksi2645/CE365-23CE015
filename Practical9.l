%{
#include "Pra9.tab.h"
%}

%%
i   { return 'i'; }
t   { return 't'; }
e   { return 'e'; }
a   { return 'a'; }
b   { return 'b'; }
\n  { return 0; }
.   { return yytext[0]; }
%%

int yywrap() {
    return 1;
}