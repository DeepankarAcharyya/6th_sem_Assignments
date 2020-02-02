#include<stdio.h>
#include<string.h>

int main(){
	//variables:
	int token_counter = 0, index1;
	char buffer[50],character;

    //printing and taking input from the user
    printf("\nEnter the index:\n");
    scanf("%d",&index1);

	// file name: test.txt
	// open the file
	FILE *fp=fopen("test.txt","r");
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
	return 0;
}