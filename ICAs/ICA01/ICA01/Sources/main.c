/********************************************************************/
// HC12 Program:  ICA #01 - [Programming Workflow]
// Processor:     MC9S12XDP512
// Bus Speed:     MHz
// Author:        JACKELYN DE JESUS
// Details:       A more detailed explanation of the program is entered here               
// Date:         January 12, 2024
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
 #define INDEX_MAX 10
/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
unsigned int counter, index;
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
PT1AD1 |= RED_LED; 
DDR1AD1 |= RED_LED;
counter = 0;
index = 0;

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
    
    if(++counter == 0)
    {
      if(++index >= INDEX_MAX)
      {
        
        index = 0; 
        PT1AD1 ^= RED_LED;
      }
    }
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/

//Questions:
//What is the purpose of the USBDM Pod? 
/*Its main purpose is to assist software developers and engineers in debugging and programming microcontrollers and other embedded devices.

// Why do we need an infinite loop when running a program in a micro-controller?
/*An infinite loop ensures that the microcontroller keeps executing its program indefinitely, which is crucial for many real-time and continuous control applications.

// When you have your code running on your board, you should see something happening. What is it?
/*Red LED flashing

//What happens if the INDEX_MAX constant define is changed from 10 to 5?
/*shortening the time when its on and off. it goes otherwise when its longer.

//What is the following line of code? DISABLE_COP();
/*a function call in an embedded systems or microcontroller programming context. 
/*It is likely used to disable the COP (Computer Operating Properly) watchdog timer.
