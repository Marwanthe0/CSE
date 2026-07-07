%{
#include <string.h>
#include "parser.tab.h"
%}

%%

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.str = strdup(yytext); 
    return ID;
}

"="     { return ASSIGN; }
"+"     { return PLUS; }
"-"     { return MINUS; }
"*"     { return MULT; }
"/"     { return DIV; }
";"     { return SEMICOLON; }
"("     { return LPAREN; }
")"     { return RPAREN; }
"{"     { return LS; }
"}"     { return RS; }
\n      { return NL; }
[ \t]   ; // Ignore whitespace
.       { printf("Unknown character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}