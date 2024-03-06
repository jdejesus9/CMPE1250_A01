/********************************************************************/
// HC12 Program:  YourProg - MiniExplanation
// Processor:     MC9S12XDP512
// Bus Speed:     40MHz
// Author:        JACKELYN DE JESUS
// Details:       A more detailed explanation of the program is entered here               
// Date:          Date Created
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
#include "pll.h"
#include "rti.h"


/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/

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
  EnableInterrupts;
  
/********************************************************************/
  // one-time initializations
/********************************************************************/
PLL_To20MHz();
SWL_Init();
RTICTL = 0b10010111;

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
    if (CRGFLG_RTIF) // RTI period over?
      {
        CRGFLG = CRGFLG_RTIF_MASK; //clear flag, VERY IMPORTANT 
        SWL_TOG (SWL_RED); 
      }
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
