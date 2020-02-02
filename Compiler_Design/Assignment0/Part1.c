//this program reads the file content and provides the line number.

#include<stdio.h>
#include<string.h>

int main(){
	//variables:
	int line_counter = 0;
	char buffer[50],character;

	// file name: test.txt
	// open the file
	FILE *fp=fopen("test.txt","r");
	
	//using fgets()
	printf("\nUsing fgets()\n");
	while(!feof(fp)){
		//read the file line
		fgets(buffer,50,fp);
		//print the file line along with the line number
		//increment the line counter
		printf("%d.%s",++line_counter,buffer);
	}	
	
	//going to the start of the file
	fseek(fp,0,SEEK_SET);
	line_counter = 0 ;
	//using fgetc()
	printf("\nUsing fgetc()\n");
	printf("\n%d.",++line_counter);
	while(!feof(fp)){
		 
		//reading
		character=fgetc(fp);
		if(character=='\n'){
			printf("%c",character);
			printf("%d.",++line_counter);
		}
		else
		//printing
		printf("%c",character);
	}
	return 0;
}

/*
fgetc():reads a character at a time;
fgets():reads a line; will read until '\n' is encountered;
fread():reads raw data; reads specified number of bytes;
*/
