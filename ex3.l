%{
#include <stdlib.h>
#define NUMBER 256
#define MAP 257
#define INC 258
#define DEC 259
#define FILTER 260
#define ODD 261
#define EVEN 262
#define CONCAT 263
extern int yylval;
%}

%%
"map" {return MAP;}
"inc" {return INC;}
"dec" {return DEC;}
"filter" {return FILTER;}
"odd" {return ODD;}
"even" {return EVEN;}
"++" {return CONCAT;}
[0-9]+ {yylval=atoi(yytext); return NUMBER;}
[(),\[\]\n] {return *yytext;}
[ \t\r] ;
. {return *yytext;}
%%
