//usage: ./a.out <filename>

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

union data{
    short num;
    char chars[2];
}d1;

int main(int argc,char *argv[]){

    //file opening 
    char file[20];
    strcpy(file,argv[1]);
    FILE* fp=fopen(file,"r");

    if(argc<2){
        printf("\nNot enough arguments!!\n");
        exit(0);
    }

    char character,chars[2];
    int no_of_characters=0,offset=0;
    printf("\n%07o ",offset);
    int number=0,number_flag=0,no_of_digits=0;

    while(!feof(fp)){
        no_of_characters++;
        character=fgetc(fp);

        if(feof(fp))
            break;
        
        if(isdigit(character)){
            no_of_characters--;
            number_flag=1;
            number=number*10+(character-'0');

            continue;
        }

        if(no_of_characters%2==0){
            d1.chars[1]=character;
        }
        else{
            d1.chars[0]=character;
        }
        if(no_of_characters%2==0)
            printf("%06o ",d1.num);

        if(no_of_characters%16==0){
            offset+=16;
            printf("\n%07o ",offset);
        }
    }
    if(no_of_characters%2==0)
            printf("000%03o",d1.chars[0]);

    //close the files
    fclose(fp);

    offset+=(no_of_characters-1)%16;
    printf("\n%07o\n",offset);

    return 0;
}