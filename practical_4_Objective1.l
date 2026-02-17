%option noyywrap
%{
	#include<stdio.h>
%}

%%
[a-z]+  { printf("%s\n", yytext); }
.       { /* Ignore other characters */ }
%%
int main()
{
	printf("enter string:");
	yylex();
	return 0;
}