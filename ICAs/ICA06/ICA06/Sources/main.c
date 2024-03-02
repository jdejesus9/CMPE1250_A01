/********************************************************************/
// HC12 Program:  PLL/Clock Library and Proof of SPEED
// Processor:     MC9S12XDP512
// Bus Speed:     40MHz
// Author:        JACKELYN DE JESUS
// Details:       A more detailed explanation of the program is entered here               
// Date:          March 01, 2024
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


/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
unsigned long count= 14300;
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
    SWL_Init();
    //Clock_Set8MHZ();
    //Clock_Set20MHZ();
    Clock_Set24MHZ();
    //Clock_EnableOutput(ClockOutDiv4);
   

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
      while(--count){
      }
      count = 14300; 
      SWL_TOG(SWL_RED);
      
     
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
