/********************************************************************/
// HC12 Program:  ICA #09 – SCI Strings and Escape Sequences 1232
// Processor:     MC9S12XDP512
// Bus Speed:     40MHz
// Author:        JACKELYN DE JESUS
// Details:       A more detailed explanation of the program is entered here               
// Date:          March 22, 2024
// Revision History :
//  each revision will have a date + desc. of changes


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


/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
int i;
int j;
int sum;
unsigned char uString[25];
unsigned char lString[25];
char uppercasevowels[] = {'A', 'E', 'I', 'O', 'U'};
char lowercasevowels[] = {'a', 'e', 'i', 'o', 'u'};   
char emptyArr[25];
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
  
/********************************************************************/c
  // one-time initializations
/********************************************************************/
SWL_Init();
Clock_Set20MHZ();

PLL_To20MHz();

sci0_InitMath(20000000,19200);

SCI0CR2 = 0b00001100;

/********************************************************************/
  // main program loop
/********************************************************************/
scio_txStr("\x1b[31m \x1b[0;0H Jackelyn De Jesus");

  for (;;)
  {
    RTI_Delay_ms(250);
    SWL_TOG(SWL_RED);

    if (SWL_Pushed(SWL_CTR))
    {
      sum = 0;
      for (i = 0; i < 20; i++)
      {
        uString[i] = uppercasevowels[(int)rand() % 5];
        sum += uString[i];
      }

      sci0_txStr("\x1b[2;2H \x1b[32m VOWELS = ");
      sprintf("\x1b[2;2H \x1b[32m VOWELS = ", uString);
      sci0_txStr(uString);

      sprintf(emptyArr, "\x1b[3;3H \x1b[33m ASCII SUM = %d", sum);
      sci0_txStr(emptyArr);
    }
    else{
      sum = 0;

      for (j = 0; j < 20; j++)
      {
        lString[j] = lowercasevowels[(int)rand() % 5];
        sum += lString[j];
      }

      sci0_txStr("\x1b[2;2H \x1b[32m VOWELS = ");
      sprintf("\x1b[2;2H \x1b[32m VOWELS = ", uString);
      sci0_txStr(lString);

      sprintf(emptyArr, "\x1b[3;3H \x1b[33m ASCII SUM = %d", sum);
      sci0_txStr(emptyArr);
    }
    
  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
