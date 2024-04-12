/********************************************************************/
// HC12 Program:  ICA10 - 7-Segment Display – Basic Functions
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        JACKELYN DE JESUS
// Details:       A more detailed explanation of the program is entered here               
// Date:          April 05, 2024
// Revision History :
// each revision will have a date + desc. of changes



/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */

//Other system includes or your includes go here


#include "sw_led.h"
//#include "clock.h"
#include "sci.h"
#include "rti.h"
#include "pll.h"
#include "segs.h"

#include <stdlib.h>
#include <stdio.h>


/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
unsigned int i;
unsigned int z;
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
  // EnableInterrupts;
  
/********************************************************************/
  // one-time initializations
/********************************************************************/
SWL_Init();
Segs_Init();

Segs_8H(7, 0b11100100);

Segs_Normal(4, '3', Segs_DP_OFF);

Segs_Custom(1, 0b1001010);
Segs_Custom(2, 0b11110000);
Segs_Custom(5, 0b10001011);
Segs_Custom(6, 0b10110001);


/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
    SWL_ON(SWL_GREEN);

    for (i = 0x0000; i <= 0xFFFF; i++)
    {
      if (SWL_Pushed(SWL_CTR))
      {
        RTI_Delay_ms(100);
        Segs_16H(i, 0);
        Segs_16H(0xFFFF - i, 1);

      }
    if (ctrPressed)
    {
      caretAnimation
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
