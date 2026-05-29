%{
#include <stdlib.h>
#define NUMBER 256
extern int yylval;
%}

%%
[0-9]+ {yylval=atoi(yytext); return NUMBER;}
"Y" {return 'Y';}
[-+^()\n] {return *yytext;}
[ \t] ;
. {return *yytext;}
%%
