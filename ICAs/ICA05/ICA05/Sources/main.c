/********************************************************************/
// HC12 Program:  ICA05 - LED and Switch Library
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        JACKELYN DE JESUS
// Details:       A more detailed explanation of the program is entered here               
// Date:          February 07, 2024
// Revision History :
// each revision will have a date + desc. of changes



/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */

#include "sw_led.h"

//Other system includes or your includes go here
//#include <stdlib.h>
//#include <stdio.h>


/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/
void TURN_ON(char LED);
void TURN_OFF(char LED);
void TOGGLE(char LED);
int GetCount(void);

/********************************************************************/
// Global Variables
/********************************************************************/
unsigned int i=0;

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
    //Tier 1
    /*
    if(SWL_Pushed(SWL_LEFT))//TURN_ON(RED_LED)
    {
      SWL_ON(SWL_RED);
    }
    else  //TURN_OFF(RED_LED)
    {
      SWL_OFF(SWL_RED); 
    }
    if(SWL_Pushed(SWL_CTR)) //TURN_ON(YELLOW_LED)
    {
      SWL_ON(SWL_YELLOW);
    }
    else  //TURN_ON(RED_YELLOW)
    {
      SWL_OFF(SWL_YELLOW); 
    }
    if(SWL_Pushed(SWL_RIGHT)) //TURN_ON(GREEN_LED)
    {
      SWL_ON(SWL_GREEN);
    }
    else  //TURN_ON(GREEN_LED)
    {
      SWL_OFF(SWL_GREEN); 
    } 
    */

    //Tier 2
    /*
    if(SWL_Pushed(SWL_LEFT))//TURN_ON(RED_LED)
    {
      SWL_ON(SWL_RED);
    }
    
    if(SWL_Pushed(SWL_CTR)) //TURN_ON(YELLOW_LED)
    {
      SWL_ON(SWL_YELLOW);
    }
    
    if(SWL_Pushed(SWL_RIGHT)) //TURN_ON(GREEN_LED)
    {
      SWL_ON(SWL_GREEN);
    }

    if(SWL_Pushed(SWL_UP))  //TURN_OFF(LED)
    {
      SWL_OFF(SWL_ALL);
    }

    if(SWL_Pushed(SWL_DOWN))  //TURN_OFF(LED)
    {
      SWL_OFF(SWL_ALL);
    }
    */

    //Tier 3
    // if(SWL_Pushed(SWL_LEFT))//TURN_ON(RED_LED)
    // {
    //   SWL_ON(SWL_RED);
    //   SWL_OFF(SWL_YELLOW);
    // }
    // if(SWL_Pushed(SWL_CTR)) //TURN_ON(YELLOW_LED)
    // {
    //   SWL_ON(SWL_YELLOW);
    //   SWL_OFF(SWL_GREEN);
    // }

    // if(SWL_Pushed(SWL_RIGHT)) //TURN_ON(GREEN_LED)
    // {
    //   SWL_ON(SWL_GREEN);
    //    SWL_OFF(SWL_RED);
    // }
    
    // if (SWL_Pushed(SWL_UP))
    // {
    //   SWL_OFF(SWL_ALL);
    // }
    // if (SWL_Pushed(SWL_DOWN))
    // {
    //   SWL_OFF(SWL_ALL);
    // }

   int count = GetCount();
      if(SWL_Pushed(SWL_LEFT)  )//TURN_ON(RED_LED)
      {
        if (count < 2){
        SWL_ON(SWL_RED);
        }
      }
      
      if(SWL_Pushed(SWL_CTR)) //TURN_ON(YELLOW_LED)
      {
        if (count < 2){
        SWL_ON(SWL_YELLOW);
        }
      }
      
      if(SWL_Pushed(SWL_RIGHT)) //TURN_ON(GREEN_LED)
      {
        if (count < 2){
        SWL_ON(SWL_GREEN);
        }
      }

     

      if(SWL_Pushed(SWL_UP))  //TURN_OFF(LED)
      {
        SWL_OFF(SWL_ALL);
      }

      if(SWL_Pushed(SWL_DOWN))  //TURN_OFF(LED)
      {
        SWL_OFF(SWL_ALL);
      }
     

  }                   
}

/********************************************************************/
// Functions
/********************************************************************/
int GetCount(void){
  int i = 0;
  if(SWL_Pushed(SWL_RED)>0) {
    i++;
  }

  if(SWL_Pushed(SWL_GREEN)>0) {
    i++;
  }
  if(SWL_Pushed(SWL_YELLOW)>0){
     i++;
  }
  return i;
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/