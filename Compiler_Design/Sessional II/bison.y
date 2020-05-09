%{
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void yyerror (char *s);

char* newtempt();

extern int yylex();
extern int yyparse();
extern FILE *yyin;

int tempt_count=0,label_count=0;

struct attribute_01{
   char* begin;
   char* after;
   char* code;
};

// struct attribute_02{
//    char* place;
//    char* code;
// };
   
%}

%start A
%union{
  struct attribute_01 *attribute_A;
  //struct attribute_02 *attribute_CM;
  char name[20];
  int val;
  char *code;
  char sym[3];
}

%token RWHILE EQUAL GREATER_THAN SMALLER_THAN N ID TRUE FALSE NOT EPSILON

%type  <attribute_A> A
%type  <name> ID C M
%type  <val>  N
%type  <code> S
%type  <sym>  R

%right  '='
%left   '+' '-' 
%left   '*' '/'
%left   ')'
%right  '('

%%

A : RWHILE '('C')' '{' S '}'
    {
      printf("\nSTART");
      printf("\nValid string\n");
      exit(0);
    }
  ;
C : ID R ID
    {
      printf("\nits ID R ID \n");
    }
    | ID R N
    {
      printf("\nits ID R N \n");
    }
    | TRUE
    {
      printf("\nits TRUE");
    }
    | FALSE
    {
      printf("\nits FALSE");
    }
    | NOT C
    {
      printf("\nits NOT C");
    }
  ;
R : EQUAL
  {
   // printf("\n %s",yylval.sym);
    strcpy($$,yylval.sym);
  }
  | GREATER_THAN
  {
   // printf("\n %s",yylval.sym);
    strcpy($$,yylval.sym);
  }
  | SMALLER_THAN
  {
   // printf("\n %s",yylval.sym);
    strcpy($$,yylval.sym);
  }
  ;
S : ID '=' M ';' S
  {
    printf("\n %s = %s ;",$1,$3);
  }
  | EPSILON
  {
    printf("\n EPSILON encountered!!");
  }
  ;
M : M'+'M
  {
    char * tempt=newtempt();
    printf("\n %s = %s + %s ;",tempt,$1,$3);
    strcpy($$,tempt);
  }
  | M'*'M
  {
    char * tempt=newtempt();
    printf("\n %s = %s * %s ;",tempt,$1,$3);
    strcpy($$,tempt);
  }
  | M'-'M
  {
    char * tempt=newtempt();
    printf("\n %s = %s - %s ;",tempt,$1,$3);
    strcpy($$,tempt);
  }
  | M'/'M
  {
    char * tempt=newtempt();
    printf("\n %s = %s / %s ;",tempt,$1,$3);
    strcpy($$,tempt);
  } 
  | '('M')'
  {
    strcpy($$,$2);
  }
  | ID
  {
    strcpy($$,$1);
  }
  | N
  {
    char * tempt=newtempt();
    printf("\n %s = %d ;",tempt,$1);
    strcpy($$,tempt);
  }
  ;

%%

void yyerror(char *s){
  printf("\nInvalid String!! nable to parse!!\n");
  fprintf(stderr,"%s\n",s);
  exit(1);
}

char* newtempt(){
  char *tempt=(char *)malloc(6*sizeof(char));
  tempt_count++;
  sprintf(tempt,"T%d",tempt_count);
  return tempt;
}

int main(void) {
    
    FILE *f1;
     
	  if (f1=fopen("input.c","r")) {
		   printf("\nfile opened!\n");
       yyin = f1;
       yyparse();
     }
    else{
      printf("\ncannot opened the file\n");
      exit(1);
    }
	  
    return 0;
}