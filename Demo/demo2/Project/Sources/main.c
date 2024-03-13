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
Segs_Init();
// do SCI startups
SCI0BD = 130; // 20E6 / (9600 * 16) // 11.3.2.1
 
SCI0CR2 = 0b00001100; // turn on TX/RX // 11.3.2.6

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
  // if the transmitter buffer is empty, load a new byte to send (TX)
  if (SCI0SR1_TDRE /*&& SWL_Transition (SWL_CTR)*/)
  SCI0DRL = rand() % 26 + 'A';
  // if a byte has been received, pull it!
  if (SCI0SR1_RDRF)
  Segs_8H (2, SCI0DRL);

  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/