%{
#include "parser.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+      { yylval = atoi(yytext); return NUMBER; }
[ \t]+      ;   // ignore spaces and tabs
\n          { return '\n'; }
.           { return yytext[0]; }  // return operators like + - * / ( )

%%

int yywrap() {
    return 1;
}