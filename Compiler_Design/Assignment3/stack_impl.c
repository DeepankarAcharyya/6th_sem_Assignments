#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<malloc.h>
#include<stdlib.h>

#define Max 32
#define N 7 //total number of production rules

int top1,top2;

struct nodes{
    char lhs; //the LHS
    char rhs[30];
};

struct nodes* production_rules; //the production rules
struct nodes* leading_set; //the leading set
struct nodes* trailing_set; //the trailing set

/*------------------------------------------------GRAMMAR---------------------------------------------------------------------
                                        S->w (C) b X e              Here w->while ; b->begin; e->end
                                        C-> O=O | O!=O | O>O | O<O 
                                        O-> N|I
                                        X->I=E;|I=E;X 
                                        E-> E+E|E*E|(E)
                                        N-> 0|1|2|3
                                        I->a|c|d

                                        terminals: ( ) = ! > < ; + * 0 1 2 3 w b e a c d
                                        non-terminals: S C X O E N I
----------------------------------------------------------------------------------------------------------------------------*/

void define_grammar(){
    production_rules=(struct nodes*)malloc(N*sizeof(struct nodes));
    leading_set=(struct nodes*)malloc(N*sizeof(struct nodes));
    trailing_set=(struct nodes*)malloc(N*sizeof(struct nodes));

    //-----------------------FIRST PRODUCTION RULE----------------------------
    production_rules[6].lhs='S';
    strcpy(production_rules[6].rhs,"w (C) b X e");
    //-----------------------SECOND PRODUCTION RULE---------------------------
    production_rules[5].lhs='C';
    strcpy(production_rules[5].rhs,"O=O|O!=O|O>O|O<O");
    //-----------------------THIRD PRODUCTION RULE----------------------------
    production_rules[4].lhs='O';
    strcpy(production_rules[4].rhs,"N|I");
    //-----------------------FOURTH PRODUCTION RULE---------------------------
    production_rules[3].lhs='X';
    strcpy(production_rules[3].rhs,"I=E;|I=E;X");
    //-----------------------FIFTH PRODUCTION RULE----------------------------
    production_rules[2].lhs='E';
    strcpy(production_rules[2].rhs,"E+E|E*E|(E)");
    //-----------------------SIXTH PRODUCTION RULE----------------------------
    production_rules[1].lhs='N';
    strcpy(production_rules[1].rhs,"0|1|2|3");
    //-----------------------SEVENTH PRODUCTION RULE---------------------------
    production_rules[0].lhs='I';
    strcpy(production_rules[0].rhs,"a|c|d");   
}

int check_terminal(char ch){
    //  printf("\n%c check if terminal\n",ch);
    if(ch=='a' ||ch=='c' ||ch=='d' ||ch=='0' ||ch=='1' ||ch=='2' ||ch=='3' ||ch=='(' || ch==')' ||ch=='=' ||ch=='!' ||ch=='>' || ch=='<' ||ch==';' ||ch=='+' ||ch=='*' ||ch=='n' ||ch=='w' ||ch=='b' ||ch=='e' )
        return 1;
    else 
        return 0;    
}

int find_production(char lhs,int j){
    // printf("\n%c check for production rule number \n",lhs);
    int i;
    for(i=0;i<N;i++){
        if(i==j)
            continue;
        if(production_rules[i].lhs==lhs){
            return i;
        }
    }
}

void add_to_set(int i,int flag,char ch){
    struct nodes* pointer;
    if(flag==0)
        pointer=leading_set;
    else
        pointer=trailing_set;

    int j;
    for(j=0;j<strlen(pointer[i].rhs);j++){
        if(pointer[i].rhs[j]==ch)
            return;
    }
    
    pointer[i].rhs[j]=ch;
    //printf("\n%s",pointer[i].rhs);
    //printf("\n%c adding to the set of %c \n",ch,pointer[i].lhs );
}

void add_to_set_string(int i,int flag,int k){
    int j;
    struct nodes* pointer;
    if(flag==0)
        pointer=leading_set;
    else
        pointer=trailing_set;


    //printf("\nString added: %s",pointer[k].rhs);

    for(j=0;j<strlen(pointer[k].rhs);j++){
       // printf("\n%c\n",pointer[k].rhs[j]);
        add_to_set(i,flag,pointer[k].rhs[j]);
    }
}

void create_leading_set(int j){
        int i,k;
    
        char lhs=production_rules[j].lhs;
        char* rhs=production_rules[j].rhs;

       // printf("\n create_leading_set: %c\n",lhs);

       for(i=0;i<top1;i++){
            // printf("\nInside search for %c against %c\n",lhs,leading_set[j].lhs);
            if(lhs==leading_set[i].lhs){
                printf("%s",leading_set[i].rhs);
                return;
            }
        }

        int index=top1;
        int flag;
        leading_set[top1++].lhs=lhs;

        for(i=0;i<10;i++){        
            // printf("\nCharacter=%c\n",rhs[i]);
            if(check_terminal(rhs[i])){
                add_to_set(index,0,rhs[i]);
            //  printf("\n%c ",rhs[i]);
                while (rhs[i] != '|' && rhs[i] != '\0')
                     i++;
            }
            else if(rhs[i]!=lhs && (rhs[i] != '|' || rhs[i] != '\0')){
                flag=0;
                //printf("\nentered else if with %c\n",rhs[i]);

                for(k=0;k<top1;k++){
                   char lhs2=leading_set[k].lhs;
                   if(rhs[i]==lhs2){
                  //      printf("found %c  %c with %s",lhs,lhs2,leading_set[k].rhs);
                        add_to_set_string(index,0,k);
                        flag=1;
                        break;
                    }
                }     

                if(flag==0){
                    // printf("\nentered else if 2 with %c\n",rhs[i]);
                    int production_rule_no=find_production(rhs[i],j);
                    create_leading_set(production_rule_no);
                }

                while (rhs[i] != '|' && rhs[i] != '\0')
                     i++;
            }

            if(rhs[i]=='\0')
                break;
        }
        printf("%s",leading_set[index].rhs);
}

void print_rules(){
    //to verify the production rules
    printf("\nTHE GRAMMAR");
    int j;
    for(j=0;j<N;j++){
        printf("\n %c -> %s",production_rules[j].lhs,production_rules[j].rhs);
    }
    printf("\n");
}


void create_trailing_set(int n){

    char lhs=production_rules[n].lhs;
    char* rhs=production_rules[n].rhs;

    int j;
    for(j=0;j<top2;j++){
            // printf("\nInside search for %c against %c\n",lhs,leading_set[j].lhs);
            if(lhs==trailing_set[j].lhs){
                printf("%s",trailing_set[j].rhs);
                return;
            }
    }
    
    int i = strlen(rhs)-1;
    int index=top2;
    int flag;
    trailing_set[top2++].lhs=lhs;

    for (; i >=0;i--){
        //printf("\nThe character is : %c\n",rhs[i]);
        if (check_terminal(rhs[i])){ 
            //printf("\ninto the check terminal if\n");
            add_to_set(index,1,rhs[i]);
            while (rhs[i] != '|' && i>0) i--;
        }
        else if (rhs[i]!=lhs && rhs[i] != '|'){
            //printf("\n into the else\n");
            flag=0;
            for(j=0;j<top2;j++){
                   char lhs2=trailing_set[j].lhs;
                   if(rhs[i]==lhs2){
                        add_to_set_string(index,1,j);
                  //      printf("\nfound %c  %c with %s",rhs[i],lhs2,leading_set[j].rhs);
                        flag=1;
                        break;
                    }
                }
            
            if(flag==0){
                //printf("\ninto the else flag==0 \n");
                int production_rule_no=find_production(rhs[i],n);
                create_trailing_set(production_rule_no);
            }
            while (rhs[i] != '|' && i!=0)
                     i--;
        }
    }
    printf("%s",trailing_set[index].rhs);
}

int main(){
    //defining the production rules
    define_grammar();
    print_rules();

    printf("\n");
    top1=0;
    top2=0;
    int i;
    
    //for the leading set
    for(i=0;i<N;i++){
        printf("\nLeading Set(%c) :",production_rules[i].lhs);
        printf(" { ");
        create_leading_set(i);
        printf(" }\n");
    }
    printf("\n----------------------------------------------------\n");
    //for the trailing set
    for(i=0;i<N;i++){
        printf("\nTrailing Set(%c) :",production_rules[i].lhs);
        printf(" { ");
        create_trailing_set(i);
        printf(" }\n");
    }
    
    return 0;
}