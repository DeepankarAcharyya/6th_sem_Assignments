//usage: ./a.out <filename>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char *argv[]){
	//variables:
	int token_counter = 0, index1;
	char buffer[50],character;

    if(argc<2){
        printf("\nNot enough arguments!!\n");
        exit(0);
    }

    //printing and taking input from the user
    printf("\nEnter the index:\n");
    scanf("%d",&index1);

	// file name: test.txt
	// open the file
    char file[20];
    strcpy(file,argv[1]);
	FILE *fp=fopen(file,"r");
	token_counter = 0 ;
	
    while(!feof(fp)){	 
		//reading
		character=fgetc(fp);

        if(character=='\n'){
            if(token_counter<index1)
                printf("(NULL)");
            token_counter=0;
            printf("%c",character);    
        }
        else
        { if (token_counter==0)
            token_counter++;
        }
        
		if(token_counter==index1){
            printf("%c",character);
        }
        
        if(character==' '){
            token_counter++;
		}
	
	}
    if(token_counter<index1 && token_counter!=0)
                printf("(NULL)");
    printf("\n");
	return 0;
}