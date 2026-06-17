%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"
%}

%%

[a-z]   {
            yylval.ch = yytext[0];
            return CHAR;
        }

"|"     { return OR; }
"."     { return CONCAT; }
"*"     { return STAR; }
"("     { return LPAREN; }
")"     { return RPAREN; }

\n      { return '\n'; }

[ \t\r]+    ;

.       {
            printf("Invalid character: %s\n", yytext);
        }

%%

int yywrap(void)
{
    return 1;
}