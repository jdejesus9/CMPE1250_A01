/********************************************************************/
// HC12 Program:  LAB02 - 16-bit Segs Functions
// Processor:     MC9S12XDP512
// Bus Speed:     40MHz
// Author:        JACKELYN DE JESUS
// Details:       A more detailed explanation of the program is entered here               
// Date:          April 17, 2024
// Revision History :
//  each revision will have a date + desc. of changes



/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */

#include "sw_led.h"
#include "segs.h"
#include "sci.h"
#include "pll.h"
//#include "clock.h"
#include "rti.h"


//Other system includes or your includes go here
#include <stdlib.h>
#include <stdio.h>


/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/
unsigned int count=0;
unsigned int count2=0;
unsigned char decimalflag=0;
//SevSegTypedef num=0;
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
SWL_Init();
//Clock_Set20MHZ();
PLL_To20MHz();
RTI_Init();
(void)sci0_Init(57600,1);
SCI0BD=22;//19200-65

//PIT_InitChannel(PIT_CH0,PIT_MT1,PIT_IEN);
//PIT_Set1msDelay(PIT_CH0);
//PIT_Start();

Segs_Init();

SWL_ON(SWL_YELLOW);

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
    Segs_ClearLine(Segs_LineBottom);  // clear all 4 decimal at the start
    
    // if(PITTF & PIT_CH0){
    //   count++;  // counter to count the ms
    // PITTF=PIT_CH0;
    // }

if(count>=200)
{
  Segs_Custom(4,0b1001010);    //print the first decimal
}
if(count>=400)
{
   Segs_Custom(5,0b1001010);   //print the second decimal
}
if(count>=600)
{
   Segs_Custom(6,0b1001010);   //print the third decimal
}
if(count>=800)
{
   Segs_Custom(7,0b1001010);   //print the last decimal
}
if(count>=1000)
{
    if(count2>9999){count2=0;}// reset the count if greater than 9999

    
    if(decimalflag) //check the decimal flag
    {
    Segs_16D(count2++,Segs_LineTop);
    }
    else
    {
      Segs_16H(count2++,Segs_LineTop);
    }

    count=0;    // reset the counter
}
  // switch responses
   if(SWL_Pushed(SWL_UP)){decimalflag=0;  // the decimal flag clear
                          SWL_ON(SWL_YELLOW);
                          SWL_OFF(SWL_GREEN);}
   if(SWL_Pushed(SWL_DOWN)){decimalflag=1;  // decimal flag ON
                          SWL_ON(SWL_GREEN);
                          SWL_OFF(SWL_YELLOW);}
   if(SWL_Pushed(SWL_CTR)) {count2=0;}
  }   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/