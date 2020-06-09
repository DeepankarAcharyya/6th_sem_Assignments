#include<reg51.h>
#include<string.h>

#define LCD P2

sbit rs = P3^0;
sbit rw = P3^1;
sbit e  = P3^2;

void Delay(unsigned int i){
    int j,k;
    for(j=0;j<i;j++)
        for(k=0;k<1275;k++);
}

void Lcd_Command(const char command){
    rs=0;
    rw=0;
    e=1;
    LCD=command;
    Delay(1);
    e=0;
}

void LcdInit(void){
    Lcd_Command(0x01);          //to clear the LCD
    Lcd_Command(0x38);          //selecting the 8bit mode and 2 lines
    Lcd_Command(0x06);          //Increment cursor (shift towards right)
    Lcd_Command(0x0c);          //Display on and cursor off
}

void display_message(const char *message){
    rs=1;
    rw=0;
    while(*message!='\0'){
        e=1;
        LCD = message;
        Delay(1)
        e=0;
        message++;
    }
}

int main(){
    short siLoop=0;
    short siLen=0;
    const char *message="Hello World!";

    siLen=strlen(message);

    LcdInit();

    while(1){
        Lcd_Command(0x8f);
        display_message(message);

        for(siLoop=0;siLoop<siLen;siLoop++){
            Lcd_Command(0x1c);
            Delay(25);
        }
    }
}