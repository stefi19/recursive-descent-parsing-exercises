%{
#include <stdlib.h>
#define NUMBER 256
#define HEAD 257
#define LENGTH 258
#define TAIL 259
#define CONCAT 260
extern int yylval;
%}

%%
"head" {return HEAD;}
"length" {return LENGTH;}
"tail" {return TAIL;}
"++" {return CONCAT;}
[0-9]+ {yylval=atoi(yytext); return NUMBER;}
[:(),\[\]\n] {return *yytext;}
[ \t\r] ;
. {return *yytext;}
%%
