#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

char while_1[]="while";
char begin_1[]="begin";
char end_1[]="end";

/*------------------------------------------------GRAMMAR---------------------------------------------------------------------
                                        S->while (C) begin X end              
                                        C-> O==O | O!=O | O>O
                                        O-> N|I
                                        X->I=E|I=EX 
                                        E-> (F);|OF;
                                        F-> +F | *F | epsilon | O
                                        N-> 0|1|2|3
                                        I->a|c|d

                                        terminals: ( ) = ! > < ; + * 0 1 2 3 a c d while begin end epsilon
                                        non-terminals: S C X O E N I
----------------------------------------------------------------------------------------------------------------------------*/

FILE * input;
char ch;
int flag_ep;

int E();
int O();
void check_separators();


int I(){
    //printf("\nI() %c\n",ch);
    //check for a
    //check for c
    //check for d
    if(ch=='a'||ch=='c'|| ch=='d'){
        ch=fgetc(input);
        check_separators();
      //  printf("\nMatched %c",ch);
        return TRUE;
    }
    else{
       // printf("\nexiting I()\n");
        return FALSE;
    }
}

int N(){//------------------------working fine
    //printf("\nN() %c\n",ch);
    //check for 0
    //check for 1
    //check for 2
    //check for 3
    if(ch=='0'||ch=='1'|| ch=='2' || ch=='3'){
        ch=fgetc(input);
        check_separators();
      //  printf("\nMatched %c",ch);
        return TRUE;
    }
    else{
        //printf("\nexiting N()\n");
        return FALSE;
    }
}

int check_epsilon(){
    flag_ep=0;
    if(ch==';'){   
        flag_ep=1;
        return TRUE;
    }
    else return FALSE;
}

int F(){
    check_separators();
    //printf("\nF() %c\n",ch);
    //check for +
    if(ch=='+'){
        //F()
        ch=fgetc(input);
        check_separators();
        return F();
    }
    
    //check for *
    else if (ch=='*'){
        ch=fgetc(input);
        check_separators();
        //F()
        return F();
    }

    //check for epsilon
    else if(check_epsilon()){ 
            return TRUE;    
    }
    else if(O()){
        return TRUE;
    }
    else{
        printf("\nError in parsing!!\nExpansion of production rule F\n");
        return FALSE;
    }
}

int X(int flag_x){
    //printf("\nX() %c\n",ch);
    //first for I()
    if(I()){
        //then for =
        //ch=fgetc(input);
        check_separators();
      //  printf("\nEntered if I() %c",ch);
        if(ch=='='){
            //then E()
            ch=fgetc(input);
            check_separators();
            if(E()){
                //then for ;
                check_separators();
        //        printf("\nsemi %c",ch);
                if(ch==';'){
                    flag_x++;
                    ch=fgetc(input);
                    check_separators();
          //          printf("\nAfter semi %c\n",ch);
                    return X(flag_x);
                    }
                else 
                return FALSE;
            }
            else return FALSE;
        }
        else return FALSE;
    }
    else {
       // printf("\n Entering else part with flag=%d\n",flag_x);
        if(flag_x==0)
            return FALSE;
        else 
            return TRUE;
        }
}

int O(){
    //printf("\nO() %c\n",ch);
    //first N()
    //then I()
    if(N() || I()){
        return TRUE;
    }
    else{   
        printf("\nError in parsing!!\nExpansion of production rule O %c\n",ch);
        exit(1);
    }
}

int E(){
    //printf("\nE() %c\n",ch);
    //first (
    if(ch=='('){
        ch=fgetc(input);
        //then F()
        if(F()){
            //ch=fgetc(input);
      //      printf("\nInto F() under E() %c\n",ch);
            //then )
            if(ch==')'){
                ch=fgetc(input);
                return TRUE;}
            else 
                return FALSE;
        }
        else return FALSE;
    }
    //or O()
    else if(O()){
        //then F()
        return F();
    }
    else{
        printf("\nError in parsing!!\nExpansion of production rule E\n");
        return FALSE;
    }
}

int C(){
    //printf("\nC() %c\n",ch);
    //first O()
    if(O()){
        // ch=fgetc(input);
      //  printf("\n inside O inside C %c\n",ch);
        if(ch=='!'){
            ch=fgetc(input);
        //    printf("\n! Matched %c\n",ch);
            if(ch=='='){
                ch=fgetc(input);
                if(O())
                    return TRUE;
                else exit(1);
            }
            else exit(1);
        }
        else if(ch=='='){
            ch=fgetc(input);
            //printf("\n= Matched %c\n",ch);
            //then for either = or != or >
            //then again for O()
            if(ch=='='){
                ch=fgetc(input);
                if(O())
                    return TRUE;
                else exit(1);
            }
            else exit(1);
        }
        else if(ch=='>'){
            ch=fgetc(input);
            //printf("\n> Matched %c\n",ch);
            if(O())
                return TRUE;
            else exit(1);
        }
        else exit(1);
    }
    else{
    printf("\nError in parsing!!\nExpansion of production rule C\n");
    exit(1);
    }
}

void check_separators(){ //---------working fine ----first char prev read
    //printf("\ncheck_separators %c\n",ch);
    while(ch==' ' || ch=='\n'){
      //  printf("\nseparator detected");
        ch=fgetc(input);
    }
    //printf("\nexit_check_separators %c\n",ch);
}

int check_while(){  //------------working fine
    //printf("\nwhile() %c\n",ch);
    int i=0;
    while(i<strlen(while_1)){
        if(ch!=while_1[i]){
            printf("\nError in parsing!!!\n");
            return FALSE;
        }
        ch=fgetc(input);
        i++;
    }
    return 1;
}

int check_begin(){//--------------------working fine
    //printf("\nbegin() %c\n",ch);
    int i=0;
    while(i<strlen(begin_1)){
        if(ch!=begin_1[i]){
            printf("\nError in parsing!!!\n Error with the BEGIN");
            return FALSE;
        }
        ch=fgetc(input);
        i++;
    }
    return 1;
}

int check_end(){
    //printf("\nend() %c\n",ch);
    int i=0;
    while(i<strlen(end_1)){
        //printf("\n%c\n",ch);
        if(ch!=end_1[i]){
            printf("\nError in parsing!!!\nERROR with the END");
            return FALSE;
        }
        ch=fgetc(input);
        i++;
    }
    return TRUE;
}

int S(){
    printf("\nParsing Started\n");
    ch=fgetc(input);
    check_separators();
    //first check for while keyword
    if(check_while()){  //--------------working fine
        check_separators();
        //then bracket (
        if(ch=='('){    //-------------working fine
            ch=fgetc(input);
            check_separators();
            //then C()  
            if(C()){    //-------------working fine
                //then bracket )
                check_separators();
                if(ch==')'){//------------working fine
                    //then keyword begin
                    ch=fgetc(input);
                    check_separators();
                    if(check_begin()){  //-------------working fine
                        check_separators();
                        //then X
                        if(X(0)){
                            check_separators();
                            //then keyword end
                            if(check_end()){
                                return 1;
                            }
                            else return FALSE;
                        }
                        else return FALSE;
                    }
                    else return FALSE;
                }
                else return FALSE;
            }
            else return FALSE; 
        }
        else return FALSE;
    }
    else return FALSE;
}


//-----------------------------------------------MAIN------------------------------------
int main(){
    //the input file
    input=fopen("sample.c","r");

   if(!feof(input)){ 
     if(S()==1){
        printf("\nParsing Complete!!\n");
        }
     else{
         printf("\nThe Input cannot be fully parsed!!\n");
     }
    }
    else printf("\nEmpty File!!!\n");
    fclose(input);
    return 0;
}