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

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
    //tier1
    int numPressed=SwitchesPressesed();

    if(SWL_Pushed(SWL_RIGHT)){    //tier3
    SWL_OFF(SWL_RED);             //tier3		
    SWL_ON(SWL_GREEN);            //tier3
    }                             //tier3
    else{                         //tier3

    //tier1
    if (numPressed > 1 || numPressed == 0){

      
        RTI_Delay_ms(10);
        SWL_TOG (SWL_RED);
      
    }

    if (SWL_Pushed(SWL_UP) > 0){
      
        RTI_Delay_ms(8);
        SWL_TOG (SWL_RED);
      
    }

    if (SWL_Pushed(SWL_DOWN) > 0){
      
        RTI_Delay_ms(12);
        SWL_TOG (SWL_RED);
      
    }

    //tier2
    if (SWL_Pushed(SWL_LEFT) > 0){

        SWL_ON(SWL_RED);
        RTI_Delay_ms(1);

        SWL_OFF(SWL_RED);
        RTI_Delay_ms(9);
      
    }

  }   
  }                
}

/********************************************************************/
// Functions
/********************************************************************/
int SwitchesPressesed(void)
{
  int i = 0;

  if (SWL_Pushed(SWL_UP) > 0)
  {
    i++;
  }

  if (SWL_Pushed(SWL_DOWN) > 0)
  {
    i++;
  }

  if (SWL_Pushed(SWL_LEFT) > 0)
  {
    i++;
  }

  if (SWL_Pushed(SWL_RIGHT) > 0)
  {
    i++;
  }
  return i;
}

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
