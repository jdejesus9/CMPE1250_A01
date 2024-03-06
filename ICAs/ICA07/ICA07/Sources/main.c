/********************************************************************/
// HC12 Program:  ICA07 - RTI Library and Blocking Delays
// Processor:     MC9S12XDP512
// Bus Speed:     40MHz
// Author:        JACKELYN DE JESUS
// Details:       A more detailed explanation of the program is entered here               
// Date:          March 06, 2024
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
#include "clock.h"

/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/
interrupt VectorNumber_Vrti void RTI_1ms (void);
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
RTI_Init();
SWL_Init();
RTICTL = 0b10010111;
//STEP 2 - ENABLE RTI
CRGINT |= CRGINT_RTIE_MASK;

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
  //   //Part 2
  //   //RTI_Delay_ms(100);
  //   //SWL_TOG(SWL_GREEN);

  //  //Part 3
  //   RTI_Delay_ms(1000);
  //   if(SWL_Pushed(SWL_LEFT)) //if Left switch is pushed, then toggle the yellow led, else toggle green led for part c
  //   {
  //   SWL_OFF(SWL_GREEN);
  //   SWL_TOG(SWL_YELLOW);
  //   }
  //   else{
  //    SWL_OFF(SWL_YELLOW);		
  //   SWL_TOG(SWL_GREEN);
  //   }
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/
interrupt VectorNumber_Vrti void RTI_1ms (void)
{
 CRGFLG = CRGFLG_RTIF_MASK; //clear flag;
 //Perform some action here
  //Part 1
  SWL_TOG(SWL_RED);
  rtiMasterCount++;
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
