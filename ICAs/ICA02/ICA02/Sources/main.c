/********************************************************************/
// HC12 Program:  ICA02 - Migrating a C# program to C
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        Jackelyn De Jesus
// Details:       A more detailed explanation of the program is entered here               
// Date:          January 17,2024
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
void RED (char bOn);
void GREEN (char bOn);
/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
unsigned int uiMainLoopCount=0;
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
  PT1AD1 &= 0x1F;
  DDR1AD1 = 0xE0;

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
    //run program loop count for RED anf GREEN LED
    ++uiMainLoopCount;
    RED(uiMainLoopCount < 0x1000);
    GREEN(uiMainLoopCount >= 0x1000);

  }                   
}

/********************************************************************/
// Functions
/********************************************************************/
void RED(char bOn){ //change the C# boolean expression to C
  if (bOn)
  PT1AD1 |= (byte)(((unsigned char)1 << (7))); //turn on RED LED
  else{
    PT1AD1 &= 0x7F; //turn off RED LED
  }
}

void GREEN(char bOn){ //change the C# boolean expression to C
  if (bOn)
  PT1AD1 |= 0x20; //turn on GREEN LED
  else{
    PT1AD1 &= 0b11011111; //turn off GREEN LED
  }
} 
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/