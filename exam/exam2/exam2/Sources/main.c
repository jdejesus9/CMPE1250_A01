/********************************************************************/
// HC12 Program:  Exam 02
// Processor:     MC9S12XDP512
// Bus Speed:     40MHz
// Author:        JACKELYN DE JESUS
// Details:       A more detailed explanation of the program is entered here               
// Date:          April 03, 2024
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
#include "sci.h"
#include "clock.h"
#include "rti.h"

/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/
int up(unsigned char receive);
/********************************************************************/
// Global Variables
/********************************************************************/
unsigned char Check;
unsigned long i=0;
unsigned long count;
unsigned char cha;
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
SWL_Init(); 
Clock_Set20MHZ();
RTI_Init();

sci0_InitMath (200000, 38400);

SCI0BD = 130;
SCI0CR2 = 0b00001100;

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
    RTI_Delay_ms(10);
    SWL_TOG(SWL_RED);
  
    
    Check = rand() % 26 + '!';
    
    if (SCI0SR1_TDRE){
      SCI0DRL = Check;
    }

    // if (SWL_PushedO(SWL_UP)){
    //   cha = SCI0DRL;
    //   if (up(cha)){
    //     SWL_UP(SWL_GREEN);
    //   }
    // }

  }                   
}

/********************************************************************/
// Functions
/********************************************************************/
int up(unsigned char receive)
{
  if (receive == '!')
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
