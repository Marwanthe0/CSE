%{
#include "parser.tab.h"
#include <ctype.h>
extern int keywords;
extern int identifiers;
extern int operators;
%}

%%

"if"|"else"|"while"|"for"|"return"  { keywords++; return KEYWORD; }

[a-zA-Z_][a-zA-Z0-9_]*             { identifiers++; return IDENTIFIER; }

"=="|"!="|[-+*/=<>]    { operators++; return OPERATOR; }
\n                               { return NEWLINE; }
[ \t0-9.,!?]+ ;
. ;
%%

int yywrap() {
    return 1;
}
