%{
#include "parser.tab.h"
#include <ctype.h>

// extern counters from parser
extern int vowels;
extern int consonants;
%}

%%

[aAeEiIoOuU]    { vowels++; }
[a-zA-Z]        { consonants++; }
\n              { return NEWLINE; }
[ \t0-9.,!?]+   ;  // ignore spaces, numbers, punctuation
.               ;  // ignore any other characters

%%

int yywrap() { return 1; }