/********************************************************************/
// HC12 Program:  Exam03
// Processor:     MC9S12XDP512
// Bus Speed:     40MHz
// Author:        JACKELYN DE JESUS
// Details:       A more detailed explanation of the program is entered here               
// Date:          April 26, 2024
// Revision History :
//  each revision will have a date + desc. of changes



/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */

//Other system includes or your includes go here
//#include <stdlib.h>
//#include <stdio.h>

#include "sw_led.h"
#include "clock.h"
#include "segs.h"
#include "lcd.h"
#include "rti.h"
#include "pll.h"
#include "sci.h"


/********************************************************************/
//Defines
/********************************************************************/
#define MAX_ROWS 2
#define MAX_COLS 16
/********************************************************************/
// Local Prototypes
/********************************************************************/
unsigned int depositedCharacters = 0;
unsigned char cursorVisible = 1;  
unsigned char cursorBlink = 0;    
unsigned char cursorX = 0;
unsigned char cursorY = 0;

int Vowel(unsigned char receive);
/********************************************************************/
// Global Variables
/********************************************************************/
char Name[] = "De Jesus";
unsigned int counter1 = 0;
unsigned char incCounter1 = 0;
unsigned char message[50];

//unsigned long ulbaud = 19200;

unsigned char cha;
unsigned char Check;
/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  //Any main local variables must be declared here
int counter = 0;
  // main entry point
  _DISABLE_COP();
  EnableInterrupts;
  
/********************************************************************/
  // one-time initializations
/********************************************************************/
SWL_Init();
lcd_Init();
Segs_Init();

RTI_Delay_ms(50);
Segs_16D(depositedCharacters, Segs_LineTop);

lcd_StringXY(0, 0, Name);
Segs_16D(counter1, Segs_LineTop); 

PLL_To20MHz();


sci0_InitMath (20000, 19200);

SCI0BD = 130;
SCI0CR2 = 0b00001100;

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
    // lcd_AddrXY(0,0);
    // lcd_String("De Jesus");

    //question D
    // if(incCounter1>=8 && !Pressed)
    //   {
    //     incCounter1 = 0; //reset variable 
        
    //     ++counter1; 
        
    //     if(counter1>9999)
    //       counter1 = 0;


    //question C
    // lcd_AddrXY(0,0);
    // lcd_String(" ");

    // lcd_AddrXY(0,2);
    // lcd_String("Alphas: 0000");

    
    // Check = rand() % 26 + 'A';
    
    // if (SCI0SR1_TDRE){
    //   SCI0DRL = Check;
    // }

    // if (SCI0SR1 & SCI0SR1_RDRF_MASK){
    //   cha = SCI0DRL;
    //   if (Vowel(cha)){
    //     SWL_ON(SWL_GREEN);
    //     SWL_OFF(SWL_YELLOW);
    //     Segs_16D(counter++, 0);
    //     //lcd_StringXY(0,0,Vowel); 
    //   }
    //   else{
    //     SWL_ON(SWL_YELLOW);
    //     SWL_OFF(SWL_GREEN);
      
    //   }

    

    //question B

    RTI_Delay_ms(50);
    SWL_TOG(SWL_RED);

    while (lcd_Busy()){
        Segs_16H(depositedCharacters, Segs_LineTop);

        // Check switch transitions
        if (SWL_PushedDeb(SWL_UP)) {
              if (cursorY > 0) {
                cursorY--;
                lcd_AddrXY(cursorX, cursorY);
                Segs_16D(counter++,0);
    }
        }
        if (SWL_PushedDeb(SWL_LEFT)) {
              if (cursorX > 0) {
                    cursorX--;
                    lcd_AddrXY(cursorX, cursorY);
                    Segs_16D(counter++,0);
                }
        }
        if (SWL_PushedDeb(SWL_RIGHT)) {
                if (cursorY < MAX_ROWS - 1) {
                    cursorY++;
                    lcd_AddrXY(cursorX, cursorY);
                    Segs_16D(counter++,0);
                }
        }
        if (SWL_PushedDeb(SWL_DOWN)) {
              if (cursorX < MAX_COLS - 1) {
                    cursorX++;
                    lcd_AddrXY(cursorX, cursorY);
                    Segs_16D(counter++,0);
                }
        }

    }
      //}

  }                   
}

/********************************************************************/
// Functions
/********************************************************************/
// int Vowel(unsigned char receive)
// {
//   if (receive == 'A' || receive == 'E' || receive == 'I' || receive == 'O'  || receive == 'U' || receive == 'a' || receive == 'e' || receive == 'i' || receive == '0'  ||receive == 'u'
//       || receive == 'B' || receive == 'b' || receive == 'C' || receive == 'c'  || receive == 'D' || receive == 'd' || receive == 'F' || receive == 'f' || receive == 'G'  ||receive == 'g'
//       || receive == 'H' || receive == 'h' || receive == 'J' || receive == 'j'  || receive == 'K' || receive == 'k' || receive == 'L' || receive == 'l' || receive == 'M'  ||receive == 'm'
//       || receive == 'N' || receive == 'n' || receive == 'P' || receive == 'p'  || receive == 'Q' || receive == 'q' || receive == 'R' || receive == 'r' || receive == 'S'  ||receive == 's'
//       || receive == 'T' || receive == 't' || receive == 'V' || receive == 'v'  || receive == 'W' || receive == 'w' || receive == 'X' || receive == 'x' || receive == 'Y'  ||receive == 'y'
//       || receive == 'Z' || receive == 'z')
//   {
//     return 1;
//   }
//   else
//   {
//     return 0;
//   }
// }
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
