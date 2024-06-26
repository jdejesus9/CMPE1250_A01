/********************************************************************/
// HC12 Program:  ICA #04 - [GPIO + AD2 Measurements]
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        JACKELYN DE JESUS
// Details:       A more detailed explanation of the program is entered here               
// Date:         January 31, 2024
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



/********************************************************************/
//Defines
/********************************************************************/
#define RED_LED 0b10000000
/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
unsigned long i=0;
unsigned int interval = 1000;
/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  //Any main local variables must be declared here

  // main entry point
  _DISABLE_COP();
  //EnableInterrupts;
  
/********************************************************************/
  // one-time initializations
/********************************************************************/
PT1AD1 &= 0x1F ;
DDR1AD1 = 0xE0;
/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
    PT1AD1 ^= RED_LED;
    for(i=0;i<210;i++)
    {


    }
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/
void TURN_ON(char LED)
{
  //set turn on LED
  PT01AD1 |= LED;
}
void TURN_OFF(char LED)
{
  PT01AD1 &= ~LED;
}

void TOGGLE(char LED)
{
  PT01AD1^= LED;
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
