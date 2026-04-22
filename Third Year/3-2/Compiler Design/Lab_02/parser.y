%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

%token NUMBER

%left '+' '-'
%left '*' '/'

%%

input: /* empty */ | input line;

line:
      expr '\n'   { printf("Result: %d\n", $1); }
    ;

expr:
      expr '+' expr   { $$ = $1 + $3; }
    | expr '-' expr   { $$ = $1 - $3; }
    | expr '*' expr   { $$ = $1 * $3; }
    | expr '/' expr   { 
                          if($3 == 0) {
                              printf("Error: Division by zero\n");
                              $$ = 0;
                          } else {
                              $$ = $1 / $3;
                          }
                       }
    | '(' expr ')'    { $$ = $2; }
    | NUMBER          { $$ = $1; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter expressions (Ctrl+Z to exit):\n");
    yyparse();
    return 0;
}