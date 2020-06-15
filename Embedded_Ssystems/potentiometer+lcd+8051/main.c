# include<reg51.h>
#include<stdio.h>

sbit ale=P3^3;  
sbit oe=P3^6; 
sbit sc=P3^4; 
sbit eoc=P3^5;  
sbit clk=P3^7;  

sbit ADDA=P3^0;  
sbit ADDB=P3^1;
sbit ADDC=P3^2;

sbit rs=P2^0;
sbit rw=P2^2;
sbit en=P2^1;


#define lcdport P2  //lcd 
#define input_port P1  //ADC

int result[3];
int number;

void timer0() interrupt 1  {
	// Function to generate clock of frequency 500KHZ using Timer 0 interrupt.
	clk=~clk;
}

void delay(unsigned int count)  {
	int i,j;
	for(i=0;i<count;i++)
		for(j=0;j<300;j++);
}

void daten(){
    rs=1;
    rw=0;
    en=1;
    delay(1);
    en=0;
}

void lcd_data(unsigned char ch){
    lcdport=ch & 0xF0;
    daten();
    lcdport=ch<<4 & 0xF0;
    daten();
}

void cmden(void){
    rs=0;
    en=1;
    delay(1);
    en=0;
}

void lcdcmd(unsigned char ch){
    lcdport=ch & 0xf0;
    cmden();
    lcdport=ch<<4 & 0xF0;
    cmden();
}

void lcdprint(unsigned char *str){
    while(*str){
        lcd_data(*str);
        str++;
    }
}

void lcd_ini(){
    lcdcmd(0x02);
    lcdcmd(0x28);
    lcdcmd(0x0e);
    lcdcmd(0x01);
	  lcdcmd(0x0c);
}

void show(){ 
   sprintf(result,"%d",number);
   lcdprint(result);
   lcdprint("  ");
}

void read_adc(){
   number=0;
   ale=1;
   sc=1;
   delay(1);
   ale=0;
   sc=0;
   while(eoc==1);
   while(eoc==0);
   oe=1;
   number=input_port;
   delay(1);
   oe=0;
}

void adc(){
    ADDC=0;
    ADDB=0;
    ADDA=0;
    lcdcmd(0xc0);		//starting of the 2nd line
    read_adc();
    show();
}

void main(){
	eoc=1;
	ale=0;
	oe=0;
	sc=0;
	TMOD=0x02;
	TH0=0xFD;
	
	lcd_ini();
	lcdcmd(192);
	//delay(500);
	lcdcmd(1);
	lcdcmd(192);
	//delay(500);
	lcdcmd(1);
	lcdprint("Reading : ");
	IE=0x82;
	TR0=1;
	
	while(1){
     adc();
     number=0;
	}
}