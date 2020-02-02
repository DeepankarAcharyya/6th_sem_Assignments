//usage: ./a.out

#include<stdio.h>
#include<string.h>

int main(int argc,char *argv[]){
	
    int roll,i=0;
    char name[20],b='\n';

    //file opening 
    //text file
    FILE* fp_text=fopen("text_q3.txt","w");
    //binary file
    FILE* fp_binary=fopen("binary_q3.bin","wb");


    while(i<10){
        //the index
        printf("\nIndex:%d",++i);
        //reading the name
        printf("\nEnter the Name:");
        scanf("%s",name);
        //reading the roll_no
        printf("\nEnter the Roll No.:");
        scanf("%d",&roll);

        //writing to the text file
        fprintf(fp_text,"%s %d\n",name,roll);
        //writing to the binary file
        //fprintf(fp_binary,"%s %d\n",name,roll);
        fwrite(name,strlen(name),1,fp_binary);
        fwrite(&roll,sizeof(int),1,fp_binary);
        fwrite(&b,sizeof(b),1,fp_binary);
    }

    //close the files
    fclose(fp_text);
    fclose(fp_binary);
	return 0;
}