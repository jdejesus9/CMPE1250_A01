/********************************************************************/
// HC12 Program:   ICA #08 – SCI Basics 1232
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        JACKELYN DE JESUS
// Details:       A more detailed explanation of the program is entered here               
// Date:          March 15, 2024
// Revision History :
// each revision will have a date + desc. of changes


/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */

//Other system includes or your includes go here
#include <stdlib.h>
#include <stdio.h>

#include "sw_led.h"
#include "pll.h"
#include "sci.h"
#include "clock.h"
#include "rti.h"
#include "segs.h"

/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/
int Vowel(unsigned char receive);
/********************************************************************/
// Global Variables
/********************************************************************/
unsigned char cha;
unsigned char Check;
//unsigned int getBaud;
/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  //Any main local variables must be declared here
int counter =0;
  // main entry point
  _DISABLE_COP();
  EnableInterrupts;
  
/********************************************************************/
  // one-time initializations
/********************************************************************/
SWL_Init();
//Clock_Set20MHZ();
PLL_To20MHz();
SCI0BD = 130;
SCI0CR2 = 0b00001100;
Segs_Init();

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
    RTI_Delay_ms(50);
    SWL_TOG(SWL_RED);

    Check = rand() % 26 + 'A';
    
    if (SCI0SR1_TDRE){
      SCI0DRL = Check;
    }

    if (SCI0SR1 & SCI0SR1_RDRF_MASK){
      cha = SCI0DRL;
      if (Vowel(cha)){
        SWL_ON(SWL_GREEN);
        SWL_OFF(SWL_YELLOW);
        Segs_16H(counter++,0);
      }
      else{
        SWL_ON(SWL_YELLOW);
        SWL_OFF(SWL_GREEN);
      
      }
    }
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/
int Vowel(unsigned char receive)
{
  if (receive == 'A' || receive == 'E' || receive == 'I' || receive == 'O'  || receive == 'U' || receive == 'a' || receive == 'e' || receive == 'i' || receive == '0'  ||receive == 'u')
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
