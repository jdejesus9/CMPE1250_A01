#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include <stdlib.h>
#include <stdio.h>

#include "lcd.h"
#include "rti.h"


/////////////////////////////////////////////////////////////////////////////
// Library Prototypes
/////////////////////////////////////////////////////////////////////////////

void lcd_Init (void){

// PIT_Sleep(PIT_CH0,25);
// PIT_Start();


/*LCD Initialization Start***************************/  
//Port Initialization-------------------------------------------    
//PH7-PH0 -> D7 - D0 (data Lines)    
DDRH = 0xFF;    
//PK2-PK0 -> Control Lines (output)    
DDRK |= 0b00000111;  
//1st delay - Delay 40+ [ms]    
// PIT_Sleep(PIT_CH2, 45);    
// //Present Data on PTH   
//  PTH  = 0b00111000;  
//  //Function Set
//  /*             
//  ||||||_____(don't care)               
//  |||||______(don't care)               
//  ||||_______font:  5x8 matrix (LOW)               
//  |||________lines: 2 (HIGH)               
//  ||_________data:  8-bit (HIGH)               
//  |__________function set of commands*/     
//  //Write Operation - Instruction Register    
//  //PK1->R/W->0  PK2->RS->0      
//  PORTK_PK1 = 0;    
//  PORTK_PK2 = 0;    
//  //PORTK &= ~(PORTA_PA1_MASK | PORTA_PA2_MASK);    
//  //Latch Instruction    
//  PORTK_PK0 = 1;    
//  lcd_MicroDelay;    
//  PORTK_PK0 = 0;    
//  //2nd Delay, 4.1ms+       
//  PIT_Sleep(PIT_CH2, 5);    
//  //Latch same Instruction again    
//  lcd_Latch;    
//  //third Delay  100uS+     
//  PIT_Delay_us(PIT_CH3, 150);
//  //third Delay  100uS+     
//  //Latch same Instruction again    
//  lcd_Latch;

//RTI_Delay_ms(45);


 
 /***************************************   
  *  *At this point, we can use the busy flag    
  * ***************************************/    
 //5x8 dots, 2 lines    
lcd_Ins(0b00111000);     
   
lcd_Ins(0b00001110);   
//display controls
/*                 
||||_____Blink:   LOW for off                   
|||______Cursor:  HIGH for on                  
||_______Display: HIGH for on                   
|________Display Control commands    
*/   
lcd_Ins(0b00000001);   
//clear display, home position    
   
lcd_Ins(0b00000110);   
//mode controls
/*|||_____Shift:   LOW for no display shift                    
    ||______Inc/Dec: HIGH for increment (to the left)                    
    |_______Entry Mode commands*/            

}


void lcd_Ins (unsigned char val){
    while(lcd_Busy()); //wait for LCD Busy
    //write command in port h
    PTH = val;

    PORTK_PK1 = 0;    
    PORTK_PK2 = 0; 

    lcd_Latch; // latch
}
 //LCD_Inst
char lcd_Busy (void){
char address;

DDRH = 0; //setting port  H as input
PORTK_PK1 = 1;    
PORTK_PK2 = 0; 
lcd_Latch; 
//Read port and mask busy bit

address = PTH & 0x80;
DDRH = 0xFF; //set port H as output 
return address;

//return busy flag

} //LCD_Inst
// char lcd_GetAddr(void){
//     char address = 0;
//     DDRH = 0x00; //set Port H as Input

//     PORTK_PK1 = 1; // Read Operation
//     PORTK_PK0 = 0; //Instruction Register

//     lcd_Latch;

//     address = PTH & 0x7F;// get 7 least significant bits, bit7 busy flag

//     DDRH = 0xFF; 
    
//     return address;
// }
void lcd_Data (unsigned char val){

    while(lcd_Busy()); //wait for LCD Busy
    //write data in port h
    PTH = val;

    PORTK_PK1 = 0;    
    PORTK_PK2 = 1; 

    lcd_Latch; // latch

}
void lcd_Addr (unsigned char addr){
    lcd_Ins(0x80 | addr); // sets the address to whatever row in the char.
}
void lcd_AddrXY (unsigned char ix, unsigned char iy){
    unsigned char Y;
    unsigned char Z;
    switch(iy){
        case 0: Y = LCD_ROW0;
        break;
        case 1: Y = LCD_ROW1;
        break;
        case 2: Y= LCD_ROW2;
        break;
        case 3: Y = LCD_ROW3;
        break;
    }
     Z = Y + ix;
    lcd_Ins(0x80 | Z);


    
}

void lcd_String (char const * straddr){
    int i = 0; // Declare and initialize 'i'
    
    // Loop through the string until the null character is encountered
    while (straddr[i] != '\0') {
        lcd_Data(straddr[i]); // Output each character
        i++; // Move to the next character
    }
}
void lcdSmartString(char const * straddr, unsigned int delay);
void lcd_StringXY (unsigned char ix, unsigned char iy, char const * const straddr){
    lcd_AddrXY(ix,iy); // calls to move cursor
    lcd_String(straddr);
}


void lcd_DispControl (unsigned char curon, unsigned char blinkon);
void lcd_Clear (void){
    lcd_Ins(0b00000001); // clear display
}
void lcd_Home (void){
    lcd_Ins(0b000000010); // go home
}
void lcd_ShiftL (char);
void lcd_ShiftR (char);
void lcd_CGAddr (unsigned char addr);
void lcd_CGChar (unsigned char cgAddr, unsigned const char* cgData, int size);