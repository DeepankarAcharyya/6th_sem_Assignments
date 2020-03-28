/*
Assignment 5:
 Implement the routines to compute the FIRST and FOLLOW sets of the non-terminals of a given grammar.
 Also, write the routine to create an LL(1) parsing table for the grammar.
Hint: Take a suitable grammar and represent it in appropriate data structures.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>

//global data-structures/variables
struct nodes{
    char lhs;
    char rhs[30];
};

struct nodes* production_rules; //the production rules
struct nodes* first_set; //the first set
struct nodes* follow_set; //the follow set

void define_grammar(){
    production_rules=(struct nodes*)malloc(5*sizeof(struct nodes));
    first_set=(struct nodes*)malloc(5*sizeof(struct nodes));
    follow_set=(struct nodes*)malloc(5*sizeof(struct nodes));

    //-----------------------FIRST PRODUCTION RULE----------------------------
    production_rules[0].lhs='E';
    strcpy(production_rules[0].rhs,"TG");
    //-----------------------SECOND PRODUCTION RULE---------------------------
    production_rules[1].lhs='G';
    strcpy(production_rules[1].rhs,"+TG|e");
    //-----------------------THIRD PRODUCTION RULE----------------------------
    production_rules[2].lhs='T';
    strcpy(production_rules[2].rhs,"FR");
    //-----------------------FOURTH PRODUCTION RULE---------------------------
    production_rules[3].lhs='R';
    strcpy(production_rules[3].rhs,"*FR|e");        //e=epsilon
    //-----------------------FIFTH PRODUCTION RULE----------------------------
    production_rules[4].lhs='F';
    strcpy(production_rules[4].rhs,"i|(E)");        //i=id
}

void print_grammar(){
    int i;
    printf("\n\t\tThe Grammar:\n");
    for(i=0;i<5;i++){
        printf("%d. %c: %s \n",i+1,production_rules[i].lhs,production_rules[i].rhs);
    }
}

int check_terminal(char ch){
    //  printf("\n%c check if terminal\n",ch);
    if(ch=='e' ||ch=='i' ||ch=='+' ||ch=='*' ||ch=='(' ||ch==')')
        return 1;
    else 
        return 0;    
}

int main(){
    define_grammar();
    print_grammar();
    return 0;
}