#include<stdio.h>
#include<string.h>

union data{
    short num;
    char chars[2];
}d1;

int main(){

    //file opening 
    FILE* fp=fopen("test1.txt","r");

    char character,chars[2];
    int no_of_characters=0,offset=0;
    printf("\n%07o ",offset);
    
    while(!feof(fp)){
        no_of_characters++;
        character=fgetc(fp);

        if(feof(fp))
            break;

        if(no_of_characters%2==0)
            d1.chars[1]=character;
        else
            d1.chars[0]=character;

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