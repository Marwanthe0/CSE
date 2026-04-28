%{
#include <stdio.h>
#include <stdlib.h>

 int keywords = 0;
 int identifiers = 0;
 int operators = 0;

void yyerror(const char *s);
int yylex();
%}

%token KEYWORD IDENTIFIER OPERATOR NEWLINE

%%

/* Recursive rule to allow multiple lines */
program:
    program line
    | line
    ;

line:
    tokens NEWLINE  {
                        printf("Keywords: %d, Identifiers: %d, Operators: %d\n",
                               keywords, identifiers, operators);
                        // Reset counts for the next line
                        keywords = 0; identifiers = 0; operators = 0;
                    }
    | NEWLINE       {
                        // Handle empty lines or just Enter key
                        printf("Keywords: %d, Identifiers: %d, Operators: %d\n",
                               keywords, identifiers, operators);
                        keywords = 0; identifiers = 0; operators = 0;
                    }
    ;

tokens:
    tokens token
    | token
    ;

token:
    KEYWORD
    | IDENTIFIER
    | OPERATOR
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter a statement:\n");
    yyparse();
    return 0;
}