%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
void yyerror(const char *s);

int tempCount = 0;
char* newTemp() {
    char* buf = (char*)malloc(10);
    sprintf(buf, "t%d", tempCount++);
    return buf;
}
%}

%union {
    char* str;
}

%token <str> ID
%token ASSIGN PLUS MINUS MULT DIV SEMICOLON LPAREN RPAREN NL LS RS
%type <str> expr

/* Precedence rules: bottom has highest priority */
%left PLUS MINUS
%left MULT DIV

%%

program:
    program statement
    | statement
    ;

statement:
    ID ASSIGN expr SEMICOLON NL { 
        printf("%s = %s\n", $1, $3); 
    }
    | NL { /* Allow blank lines */ }
    ;

expr:
    expr PLUS expr {
        char* temp = newTemp();
        printf("%s = %s + %s\n", temp, $1, $3);
        $$ = temp;
    }
    | expr MINUS expr {
        char* temp = newTemp();
        printf("%s = %s - %s\n", temp, $1, $3);
        $$ = temp;
    }
    | expr MULT expr {
        char* temp = newTemp();
        printf("%s = %s * %s\n", temp, $1, $3);
        $$ = temp;
    }
    | expr DIV expr {
        char* temp = newTemp();
        printf("%s = %s / %s\n", temp, $1, $3);
        $$ = temp;
    }
    | LPAREN expr RPAREN {
        /* Parentheses group things but do not generate a TAC instruction themselves */
        $$ = $2; 
    }
    | LS expr RS {
        /* Parentheses group things but do not generate a TAC instruction themselves */
        $$ = $2; 
    }
    | ID {
        $$ = $1;
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}

int main() {
    printf("Enter an expression:\n");
    yyparse();
    return 0;
}