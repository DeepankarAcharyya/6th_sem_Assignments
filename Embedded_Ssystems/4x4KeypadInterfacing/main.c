#include <reg51.h>

sbit RowA = P1 ^ 0; //RowA
sbit RowB = P1 ^ 1; //RowB
sbit RowC = P1 ^ 2; //RowC
sbit RowD = P1 ^ 3; //RowD

sbit C1 = P1 ^ 4; //Column1
sbit C2 = P1 ^ 5; //Column2
sbit C3 = P1 ^ 6; //Column3
sbit C4 = P1 ^ 7; //Column4

sbit E = P3 ^ 6;  //E pin for LCD
sbit RS = P3 ^ 7; //RS pin for LCD

void init(void)
{
    P0 = 0x00; //not used
    P1 = 0xf0; //used for generating outputs and taking inputs from Keypad
    P2 = 0x00; //used as data port for LCD
    P3 = 0x00; //used for RS and E
}

void delay(int a)
{
    int i,j;
    for (i = 0; i < a; i++)
        for (j = 0; j < 112; j++);
}

void writedata(char t)
{
    RS = 1; // This is data
    P2 = t; //Data transfer
    E = 1;  // => E = 1
    delay(5);
    E = 0; // => E = 0
    delay(5);
}

void send_msg(char *msg)
{
    int i = 0;
    while (msg[i] != '\0')
    {
        writedata(msg[i]);
        i++;
    }
}

void writecmd(int z)
{
    RS = 0; // This is command
    P2 = z; //Data transfer
    E = 1;  // => E = 1
    delay(100);
    E = 0; // => E = 0
    delay(100);
}

void lcd_init(void)
{
    writecmd(0x38); //function set
    writecmd(0x0c); //display on,cursor off,blink off
    writecmd(0x01); //clear display
    writecmd(0x06); //entry mode, set increment
    writecmd(0x80); //force cursor to beginning of first line
}

int read_keypad(void)
{
    RowA = 0;
    RowB = 1;
    RowC = 1;
    RowD = 1; //Test Row A

    if (C1 == 0) { delay(50); while (C1 == 0); return 7; }
    if (C2 == 0) { delay(50); while (C2 == 0); return 8; }
    if (C3 == 0) { delay(50); while (C3 == 0); return 9; }
    if (C4 == 0) { delay(50); while (C4 == 0); return 10; } // div

    RowA = 1;
    RowB = 0;
    RowC = 1;
    RowD = 1; //Test Row B

    if (C1 == 0) { delay(50); while (C1 == 0); return 4; }
    if (C2 == 0) { delay(50); while (C2 == 0); return 5; }
    if (C3 == 0) { delay(50); while (C3 == 0); return 6; }
    if (C4 == 0) { delay(50); while (C4 == 0); return 11;} //x

    RowA = 1;
    RowB = 1;
    RowC = 0;
    RowD = 1; //Test Row C

    if (C1 == 0) { delay(50); while (C1 == 0); return 1; }
    if (C2 == 0) { delay(50); while (C2 == 0); return 2; }
    if (C3 == 0) { delay(50); while (C3 == 0); return 3; }
    if (C4 == 0) { delay(50); while (C4 == 0); return 12;} //sub

    RowA = 1;
    RowB = 1;
    RowC = 1;
    RowD = 0; //Test Row D

    if (C1 == 0) { delay(50); while (C1 == 0); return 13; }//C
    if (C2 == 0) { delay(50); while (C2 == 0); return 0;  }
    if (C3 == 0) { delay(50); while (C3 == 0); return 14; }//=
    if (C4 == 0) { delay(50); while (C4 == 0); return 15; }//+

    return -1; 
}

int get_pressed_key(void) 
{
    int key = -1;
    while (key == -1 )  
        key = read_keypad(); 

    return key;
}

int main(void)
{
    int key;

    init();
    lcd_init();

    while (1)
    {
        key = get_pressed_key(); 
        writecmd(0x01);        // Clear screen
        switch(key){
            case 1: send_msg("ONE");   break;
            case 2: send_msg("TWO");   break;
            case 3: send_msg("THREE"); break;
            case 4: send_msg("FOUR");  break;
            case 5: send_msg("FIVE");  break;
            case 6: send_msg("SIX");   break;
            case 7: send_msg("SEVEN"); break;
            case 8: send_msg("EIGHT"); break;
            case 9: send_msg("NINE");  break;
            case 0: send_msg("ZERO");  break;
            case 10: send_msg("DIV");  break;
            case 11: send_msg("MUL");  break;
            case 12: send_msg("SUB");  break;
            case 13: send_msg("CLR");  break;
            case 14: send_msg("EQL");  break;
            case 15: send_msg("ADD");  break;
                }
    }
}
