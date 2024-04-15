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
unsigned int j;
unsigned char z[] =
{
  0b11000000, // a top
  0b10100000, // b top right
  0b10010000, // c bottom right
  0b10000001, // d bottom
  0b10001000, // e bottom left
  0b10000010, // f top left
};
/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  //Any main local variables must be declared here
  unsigned int i = 0;
  unsigned int ctrPressed = 0;
  unsigned int zPosition = 0;
  unsigned int zAnimationPos = 0;
  unsigned int loopCount = 0;
  unsigned int zMovedTotal = 0;

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
    //tier 1
    if (SWL_Pushed(SWL_CTR))
    {
      ctrPressed = 1;

      Segs_16H(i, 0);

      Segs_16H(0xFFFF - i, 1);
      i++;
    }

    //tier 2
    if (ctrPressed)
    {
      zAnimationPos = (zAnimationPos + 1) % 6;

      Segs_Custom(zPosition, z[zAnimationPos]);

      if (SWL_Pushed(SWL_RIGHT))
      {
        loopCount++;

        if (loopCount >= 10)
        {
         Segs_ClearLine(Segs_LineTop);
         zPosition = (zPosition + 1) % 4;

         zMovedTotal++;
         loopCount = 0; 
        }
      }
      else if (SWL_Pushed(SWL_LEFT))
      {
        loopCount++;

        if (loopCount >= 10)
        {
         Segs_ClearLine(Segs_LineTop);
         zPosition--;
         zPosition = (zPosition % 4 + 4) % 4;
         zMovedTotal++;

         loopCount = 0; 
        }
      }

      Segs_16H(zMovedTotal, 1); 
    }

    RTI_Delay_ms(100);
    

  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
