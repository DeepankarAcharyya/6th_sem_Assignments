#include<stdio.h>

__global__ void mykernel(void){
}

int main(){
    mykernel<<<1,1>>>();
    printf("Helo World!\n");
    return 0;
}