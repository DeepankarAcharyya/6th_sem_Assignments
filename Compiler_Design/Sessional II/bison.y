%{

%}

%token RWHILE EQUAL GREATER_THAN SMALLER_THAN N ID TRUE FALSE NOT EPSILON
%right  '=' '('
%left   '+' '-' ')'
%left   '*' '/'
%left   ')'

%%

A : RWHILE '('C')' '{'S'}'
C : ID R ID
  | ID R N
  | TRUE
  | FALSE
  | NOT C
R : EQUAL
  | GREATER_THAN
  | SMALLER_THAN
S : ID '=' M ';'
  | EPSILON
M : M '+' M
  | M '*' M
  | M '-' M
  | M '/' M 
  | '(' M ')'
  | ID
  | N

%%
#include "lex.yy.c"
#include<stdio.h>
#include<string.h>


int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Kindly provide the file name.\n like ./a.out file_name.c\n\n");
        exit(1);
    }
    yyin = fopen(argv[1], "r");
    yyparse();
    return 0;
}
