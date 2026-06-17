%code requires {

typedef struct Node
{
    char value;
    struct Node *left;
    struct Node *right;
} Node;

}

%{

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

Node *root = NULL;

Node *createNode(char value, Node *left, Node *right);
void printTree(Node *root, int level);

int yylex(void);
void yyerror(const char *s);

%}

%union
{
    char ch;
    Node *node;
}

%token <ch> CHAR
%token OR CONCAT STAR LPAREN RPAREN

%left OR
%left CONCAT
%right STAR

%type <node> expr

%%

input
    : expr '\n'
      {
          root = $1;

          printf("\nSyntax Tree:\n\n");
          printTree(root, 0);
          printf("\n");
      }
    ;

expr
    : expr OR expr
      {
          $$ = createNode('|', $1, $3);
      }
    | expr CONCAT expr
      {
          $$ = createNode('.', $1, $3);
      }
    | expr STAR
      {
          $$ = createNode('*', $1, NULL);
      }
    | LPAREN expr RPAREN
      {
          $$ = $2;
      }
    | CHAR
      {
          $$ = createNode($1, NULL, NULL);
      }
    ;

%%

Node *createNode(char value, Node *left, Node *right)
{
    Node *temp = (Node *)malloc(sizeof(Node));

    if (temp == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    temp->value = value;
    temp->left = left;
    temp->right = right;

    return temp;
}

void printTree(Node *root, int level)
{
    int i;

    if(root == NULL)
        return;

    printTree(root->right, level + 1);

    for(i = 0; i < level; i++)
        printf("    ");

    printf("%c\n", root->value);

    printTree(root->left, level + 1);
}

void yyerror(const char *s)
{
    printf("Parse Error: %s\n", s);
}

int main(void)
{
    printf("Enter Regular Expression:\n");
    yyparse();
    return 0;
}