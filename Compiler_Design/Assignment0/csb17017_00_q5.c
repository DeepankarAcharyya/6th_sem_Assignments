//usage: ./a.out <filename>

#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int main(int argc,char *argv[]){
    
    char file[20],buffer[100],character;

    if(argc<2){
        printf("\nNot enough arguments!!\n");
        exit(0);
    }

    strcpy(file,argv[1]);
    FILE* fp=fopen(file,"r");

    while(!feof(fp)){
		character=fgetc(fp);
        
        if(isprint(character) || character=='\t'){
           // printf("%c",character);          
            sprintf(buffer,"%s%c",buffer,character);
          }
        else{
            if (strlen(buffer) > 3)
                printf("%s\n",buffer);
            buffer[0]='\0';
        }
	}
    
    fclose(fp);
    return 0;
}