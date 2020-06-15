#include<reg51.h>
void delay(unsigned int t);
void main()
{
unsigned int ch[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
unsigned int i,j;
P3=0xc0;
P2=0xc0;

while(1)
{
for(j=0;j<10;j++)	
{
for(i=0;i<10;i++)
{
P3=ch[i];
delay(50);
}
if(j!=10)
P2=ch[j+1];
}
if(i==10&&j==10)
P3=0xc0;
P2=0xc0;
}
}
void delay(unsigned int t)
{
unsigned int i,j;
for(i=0;i<t;i++)
for(j=0;j<1275;j++);
}