%{
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void yyerror (char *s);

char* newlabel();

extern int yylex();
extern int yyparse();
extern FILE *yyin;

int temp_count=0,label_count=0;

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
    printf("\nEQUAL encountered!!");
  }
  | GREATER_THAN
  {
    printf("\nGT encountered!!");
  }
  | SMALLER_THAN
  {
    printf("\nST encountered!!");
  }
  ;
S : ID '=' M ';' S
  {
    printf("\n Id=M ");
  }
  | EPSILON
  {
    printf("\n EPSILON encountered!!");
  }
  ;
M : M'+'M
  {
    char * label=newlabel();
    printf("\n %s = %s + %s ;",label,$1,$3);
    strcpy($$,label);
  }
  | M'*'M
  {
    char * label=newlabel();
    printf("\n %s = %s * %s ;",label,$1,$3);
    strcpy($$,label);
  }
  | M'-'M
  {
    char * label=newlabel();
    printf("\n %s = %s - %s ;",label,$1,$3);
    strcpy($$,label);
  }
  | M'/'M
  {
    char * label=newlabel();
    printf("\n %s = %s / %s ;",label,$1,$3);
    strcpy($$,label);
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
    char * label=newlabel();
    printf("\n %s = %d ;",label,$1);
    strcpy($$,label);
  }
  ;

%%

void yyerror(char *s){
  printf("\nInvalid String!! nable to parse!!\n");
  fprintf(stderr,"%s\n",s);
  exit(1);
}

char* newlabel(){
  char *label=(char *)malloc(6*sizeof(char));
  label_count++;
  sprintf(label,"L%d",label_count);
  printf("\nNew label:%s\n",label);
  return label;
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