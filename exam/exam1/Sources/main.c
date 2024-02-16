/********************************************************************/
// HC12 Program:  Practical Assessment #1
// Processor:     MC9S12XDP512
// Bus Speed:     40MHz
// Author:        JACKELYN DE JESUS
// Details:       A more detailed explanation of the program is entered here               
// Date:          February 16, 2024
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

/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
//part A
unsigned long i=0;

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

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
    // SWL_ON(SWL_ALL);   //preparation

    //part A
    // SWL_ON(SWL_RED);
    // for(i=0;i<2557;i++)
    // {

    // }
    // SWL_OFF(SWL_RED);
    // for(i=0;i<852;i++)
    // {

    // }

    //part B
   int pressed = Switches();

   SWL_ON(SWL_RED);
    for(i=0;i<2557;i++)
    {

    }
    SWL_OFF(SWL_RED);
    for(i=0;i<852;i++)
    {

    }

   if(pressed == 2)
   {
    SWL_ON(SWL_GREEN);
    SWL_OFF(SWL_YELLOW);
    
   }

  
   else
   {
    SWL_ON(SWL_YELLOW);
    SWL_OFF(SWL_GREEN);
    
   }

  }                   
}

/********************************************************************/
// Functions
/********************************************************************/
//part A
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

//part B
int Switches(void)
{
  int i = 0;
  if(SWL_Pushed(SWL_LEFT)>0) 
  {
    i++;
  }
  if(SWL_Pushed(SWL_RIGHT)>0)
  {
    i++;
  } 
  if(SWL_Pushed(SWL_UP)>0) 
  {
    i++;
  }
  if(SWL_Pushed(SWL_DOWN)>0) {
    i++;
  }
  if(SWL_Pushed(SWL_CTR)>0) {
    i++;
  }
  
  return i;
}


/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
