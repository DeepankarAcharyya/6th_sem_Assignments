%{
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
//#include "lex.yy.c"
//char* newlabel();
//char* newtemp();
//char* generate();
void yyerror (char *s);


extern int yylex();
extern int yyparse();
extern FILE *yyin;

int temp_count=0,label_count=0;

struct attribute_01{
   char* begin;
   char* after;
   char* code;
};

struct attribute_02{
   char* place;
   char* code;
};
   
%}

%start A
%union{
  struct attribute_01 *attribute_A;
  struct attribute_02 *attribute_CM;
  char name[20];
  int val;
  char *code;
  char sym[20];
}

%token RWHILE EQUAL GREATER_THAN SMALLER_THAN N ID TRUE FALSE NOT EPSILON

%type  <attribute_A> A
%type  <attribute_CM> C M
%type  <name> ID
%type  <val>  N
%type  <code> S
%type  <sym>  R

%right  '='
%left   '+' '-' 
%left   '*' '/'
%left   ')'
%right  '('

%%

A : RWHILE '('C')' '{'S'}'
    {
      printf("\nSTART");
    }
  ;
C : ID R ID
    {
      printf("\nits ID R ID");
    }
    | ID R N
    {
      printf("\nits ID R N");
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
S : ID '=' M ';'
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
    printf("\nM+M");
  }
  | M'*'M
  {
    printf("\nM*M");
  }
  | M'-'M
  {
    printf("\nM-M");
  }
  | M'/'M
  {
    printf("\nM/M");
  } 
  | '('M')'
  {
    printf("\nM");
  }
  | ID
  {
    printf("\nID");
  }
  | N
  {
    printf("\nN");
  }
  ;

%%
// char *newlabel(){
// 	char *label = (char *)malloc(10*sizeof(char));
// 	strcpy(label,"L");
// 	label_count++;
//   sprintf(labelArray,"%d",label_count);
// 	emit(label,labelArray);	
	
// 	return label;
// }

// char * newtemp(){
// 	char *newTemp = (char *)malloc(30);
// 	strcpy(newTemp,"t");
// 	sprintf(numberArray,"%d",n);
// 	emit(newTemp,numberArray);
// 	n++;
// 	return newTemp;
// }

int main(void) {
    // int argc, char *argv[]
    // if(argc < 2) {
    //     printf("Kindly provide the file name.\n like ./a.out file_name.c\n\n");
    //     exit(1);
    // }
    
    // FILE *f1 = fopen(argv[1], "r");
    
    FILE *f1 =fopen("csb7017_input.c","r");
	  // if (!f1) {
		//   printf("Cannot open file");
		//   exit(1);
	  // }

	  yyin = f1;
    yyparse();

    return 0;
}
  
void yyerror(char *s){
  fprintf(stderr,"%s\n",s);
}