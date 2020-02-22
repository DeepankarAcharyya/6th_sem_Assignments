#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 16

struct element{
    int type; //number->0      operators->1
    int value; //for operators: +:0     -:1     *:2     /:3     %:4
};

int main(){
    char ch;
    int i=0;
    struct element* ptr=(struct element *)malloc(MAX*sizeof(struct element));

    printf("\nEnter the expression:\n");
    ch=getc(stdin);

    while(ch!=';'){
        //check for numbers
        if(isdigit(ch)!=0){
            ptr[i].type=0;
            ptr[i].value=ch - '0';
        }
        //check for operators
        else if(ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='%' ){
            ptr[i].type=1;

            if(ch=='+')
                ptr[i].value=0;
            else if(ch=='-')
                ptr[i].value=1;
            else if(ch=='*')
                ptr[i].value=2;
            else if(ch=='/')
                ptr[i].value=3;
            else if(ch=='%')
                ptr[i].value=4;

        }

        printf("%c",ch);
        ch=getc(stdin);
        i++;
    }
    printf("*****");
    int t=0;
    printf("\n-------------Checking!!------------------\n");
    for(;t<i;t++){
        printf("%d  Value:%d    Type:%d\n",t,ptr[t].value,ptr[t].type);
    }

    printf("\nThe End");
    return 0;
}