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

int flag=0;

%}

%start A

%union{
  char name[20];
  int val;
  char sym[3];
}

%token RWHILE EQUAL GREATER_THAN SMALLER_THAN N ID TRUE FALSE NOT 

%type  <val> A
%type  <name> ID C M
%type  <val>  N
%type  <val> S
%type  <sym>  R

%right  '='
%left   '+' '-' 
%left   '*' '/'
%left   ')'
%right  '('

%%
A : RWHILE '(' C ')' '{' S '}' 
    {
      char * end=terminate(start_count);
      char * begin=initialize(start_count);
      flag=0;
      printf("\n goto %s ; \n %s : ",begin,end);
      printf("\n********SUCCESSFULLY PARSED*********\n");
      flag=0;
      $$=1;
    }
  ;
C : ID R ID
    {
      char * begin = initialize(++start_count);
      printf("\n%s : ",begin);
  
      char * tempt=newtempt();
      printf(" %s = %s %s %s;",tempt,$1,$2,$3);
      char * end=terminate(start_count);
      
      if(flag==0)
          printf("\n if %s == False goto %s ;",tempt,end);
      else{
          char * tempt2=newtempt();
          printf("\n %s = ~ ( %s );",tempt2,tempt);
          printf("\n if %s == False goto %s ;",tempt2,end);
      }

      strcpy($$,tempt);
    }
    | ID R N
    {
      char * begin = initialize(++start_count);
      printf("\n%s : ",begin);
      
      char * tempt=newtempt();
      printf(" %s = %s %s %d;",tempt,$1,$2,$3);
      char * end=terminate(start_count);
      
      if(flag==0)
          printf("\n if %s == False goto %s ;",tempt,end);
      else{
          char * tempt2=newtempt();
          printf("\n %s = ~ ( %s );",tempt2,tempt);
          printf("\n if %s == False goto %s ;",tempt2,end);
      }
      
      strcpy($$,tempt);
    }
    | TRUE
    {
      
      char * begin = initialize(++start_count);
      printf("\n%s : ",begin);
        
      char * tempt=newtempt();
      char * end=terminate(start_count);
      
      printf(" %s = True ;",tempt);
      
      if(flag==0)
          printf("\n if %s == False goto %s ;",tempt,end);
      else{
          char * tempt2=newtempt();
          printf("\n %s = ~ ( %s );",tempt2,tempt);
          printf("\n if %s == False goto %s ;",tempt2,end);
      }

      strcpy($$,tempt);
    }
    | FALSE
    {
      
      char * begin = initialize(++start_count);
      printf("\n%s : ",begin);
        
      char * tempt=newtempt();
      char * end=terminate(start_count);

      printf(" %s = False ;",tempt);
        
      if(flag==0)
          printf("\n if %s == False goto %s ;",tempt,end);
      else{
          char * tempt2=newtempt();
          printf("\n %s = ~ ( %s );",tempt2,tempt);
          printf("\n if %s == False goto %s ;",tempt2,end);
      }

      strcpy($$,tempt);
    }
    | NOT C
     {
        flag=0;
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
S : /* empty */ 
  { 
    $$=1;
  }
  |  ID '=' M ';' S
  {
    $$=$5;
    printf("\n %s = %s ;",$1,$3);
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
  printf("\n\n\n\n\n\nInvalid String!! unable to parse!!\n");
  fprintf(stderr,"%s\n\n\n\n",s);
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
       yyin = f1;
       yyparse();
     }
    else{
      printf("\ncannot opened the file\n");
      exit(1);
    }
	  
    return 0;
}