#include<stdio.h>
#include<string.h>
#include<ctype.h>

int main(int argc,char *argv[]){
    
    char file[20],buffer[5],character;
    int index=0,no_of_characters=0;

    strcpy(file,argv[1]);
    FILE* fp=fopen(file,"r");

    while(!feof(fp)){
		character=fgetc(fp);
        if(isprint(character)!=0){
           // printf("%c",character);          
            buffer[index++]=character;
            no_of_characters++;

            if(index==4){
                printf("%s",buffer);
                buffer[0]='\0';
                index=0;
          }
        }

        if(character=='\n'){
            if(no_of_characters<4){
                no_of_characters=0;
                buffer[0]='\0';
                index=0;   
                continue;
                }

            buffer[index]='\0';
            printf("%s",buffer);
            no_of_characters=0;
            printf("\n");
            buffer[0]='\0';
            index=0;
        }
	}

    fclose(fp);
    return 0;
}