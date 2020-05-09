%{
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void yyerror (char *s);

char* newtempt();
char* newlabel();
char* initialize(int i);
char* terminate(int i);

extern int yylex();
extern int yyparse();
extern FILE *yyin;

int tempt_count=0,label_count=0,start_count=0;

struct attribute_01{
   char* begin;
   char* after;
   char* code;
};

%}

%start A
%union{
  struct attribute_01 *attribute_A;
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

A : RWHILE {char * begin=initialize(++start_count);printf("\n %s :",begin);} '('C')' '{' S '}' {char * end=terminate(start_count);printf("\n %s :",end);}
  ;
C : ID R ID
    {
      //printf("\nits ID R ID \n");
      char * tempt=newtempt();
      printf(" %s = %s %s %s;",tempt,$1,$2,$3);
      strcpy($$,tempt);
    }
    | ID R N
    {
      //printf("\nits ID R N \n");
      char * tempt=newtempt();
      printf(" %s = %s %s %d;",tempt,$1,$2,$3);
      strcpy($$,tempt);
    }
    | TRUE
    {
      //printf("\nits TRUE \n");
      char * tempt=newtempt();
      printf(" %s = True ;",tempt);
      strcpy($$,tempt);
    }
    | FALSE
    {
      //printf("\nits FALSE \n");
      char * tempt=newtempt();
      printf(" %s = False ;",tempt);
      strcpy($$,tempt);
    }
    | NOT C
    {
      //printf("\nits Not C \n");
      char * tempt=newtempt();
      printf(" %s = ~ %s ;",tempt,$2);
      strcpy($$,tempt);
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
    //printf("\n EPSILON encountered!!");
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

char* newlabel(){
  char *label=(char *)malloc(10*sizeof(char));
  label_count++;
  sprintf(label,"Label%d",tempt_count);
  return label;
}

char* initialize(int i){
  char *label=(char *)malloc(10*sizeof(char));
  sprintf(label,"START%d",i);
  return label;
}

char* terminate(int i){
  char *label=(char *)malloc(10*sizeof(char));
  sprintf(label,"END%d",i);
  return label;
}

int main(void) {
    
    FILE *f1;
     
	  if (f1=fopen("input.c","r")) {
		   //printf("\nfile opened!\n");
       yyin = f1;
       yyparse();
     }
    else{
      printf("\ncannot opened the file\n");
      exit(1);
    }
	  
    return 0;
}