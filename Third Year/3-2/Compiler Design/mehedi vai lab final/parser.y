%{
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void yyerror(const char *s);
int yylex();

int tempCount = 0;

char code[500][100];
int codeIndex = 0;

char* newTemp()
{
    char *t = (char*)malloc(20);
    sprintf(t,"t%d",tempCount++);
    return t;
}

void emit(char *s)
{
    strcpy(code[codeIndex++],s);
}

void printCode()
{
    int i;
    for(i=0;i<codeIndex;i++)
        printf("%s\n",code[i]);
}

void clearCode()
{
    codeIndex=0;
}
%}

%union{
    char *str;
}

%token <str> ID NUM
%type <str> E T F

%left '+' '-'
%left '*' '/'

%%

program:
      program line
    |
    ;

line:
      stmt ';' '\n'
      {
          printCode();
          clearCode();
      }
    | stmt ';'
      {
          printCode();
          clearCode();
      }
    | error '\n'
      {
          printf("Syntax Error\n");
          clearCode();
          yyerrok;
      }
    ;

stmt:
      ID '=' E
      {
          char buf[100];
          sprintf(buf,"%s = %s",$1,$3);
          emit(buf);
      }
    ;

E:
      E '+' T
      {
          char *t=newTemp();
          char buf[100];
          sprintf(buf,"%s = %s + %s",t,$1,$3);
          emit(buf);
          $$=t;
      }
    | E '-' T
      {
          char *t=newTemp();
          char buf[100];
          sprintf(buf,"%s = %s - %s",t,$1,$3);
          emit(buf);
          $$=t;
      }
    | T
      {
          $$=$1;
      }
    ;

T:
      T '*' F
      {
          char *t=newTemp();
          char buf[100];
          sprintf(buf,"%s = %s * %s",t,$1,$3);
          emit(buf);
          $$=t;
      }
    | T '/' F
      {
          char *t=newTemp();
          char buf[100];
          sprintf(buf,"%s = %s / %s",t,$1,$3);
          emit(buf);
          $$=t;
      }
    | F
      {
          $$=$1;
      }
    ;

F:
      '(' '(' E '}' '}'
      {
          $$ = $3; /* $3 corresponds to the expression E position */
      }
    | '{' '{' E ')' ')'
      {
          $$ = $3; /* $3 corresponds to the expression E position */
      }
    | ID
      {
          $$ = $1;
      }
    | NUM
      {
          $$ = $1;
      }
    ;

%%

void yyerror(const char *s)
{
}

int main()
{
    printf("Enter Statements:\n");
    yyparse();
    return 0;
}