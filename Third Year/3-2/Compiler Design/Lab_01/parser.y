%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();

// Global counters
int vowels = 0;
int consonants = 0;
%}

%token NEWLINE

%%

input:
      /* empty */
    | input line
    ;

line:
      NEWLINE { 
          printf("Vowels: %d, Consonants: %d\n", vowels, consonants); 
          vowels = 0; consonants = 0; 
      }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter statements (Ctrl+Z then Enter to end):\n");
    yyparse();
    return 0;
}