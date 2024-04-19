/********************************************************************/
// HC12 Program:  LAB01
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        JACKELYN DE JESUS
// Details:       A more detailed explanation of the program is entered here
// Date:          April 04, 2024
// Revision History :
// each revision will have a date + desc. of changes

/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */


#include "clock.h"
#include "rti.h"
#include "sci.h"
#include "sw_led.h"


//Other system includes or your includes go here
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
unsigned char message[200];
unsigned int RedLedDelayCounter=0;
unsigned int RedLedDelay=50;
unsigned char data;
unsigned char flag=0;
unsigned char rx_Message[200];
unsigned int index=0;
unsigned int forCheck;
SwState switchState;
SwState switchState2;

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
// Clock_Set20MHZ();
RTI_Init();
// (void)sci0_Init(115200,1);
// SCI0BD=11;
/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
   {
    //Part A
    if(RedLedDelayCounter>=RedLedDelay)
    {
      RedLedDelayCounter=0;
      SWL_TOG(SWL_RED);
    }
  //Part B
    if(Sw_Process(&switchState,SWL_UP)==Released)
  {
    PT1AD1 &= 0b00011111;
    RedLedDelay+=10;
    if(RedLedDelay>100){RedLedDelay=100;}
  }
  if(Sw_Process(&switchState2,SWL_DOWN)==Released)
  
  {
    PT1AD1 &= 0b00011111;
    RedLedDelay-=10;
    if(RedLedDelay<10){RedLedDelay=10;}
  }

  //Part C
   if(flag)
      {     
        index = 0;
        flag = 0;
      if(sscanf(rx_Message, "%d",&forCheck))
      {
        if(forCheck>100||forCheck<10)
        {
          (void)sprintf(message, "Wrong setting, number must be between 10 and 100 inclusive\r\n"); }
        else
        {
          (void)sscanf(rx_Message, "%d",&RedLedDelay);
          (void)sprintf(message, "RTI event set to  = %d [ms]\r\n",RedLedDelay);
        }
      }        
       else
            {
            (void)sprintf(message, "Input in Wrong format\r\n"); 
            }
        
        sci0_txStr(message);
        (void)memset(rx_Message,0,sizeof(rx_Message));
   }
   
  }
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
 interrupt VectorNumber_Vrti void Vrti_ISR(void)
   {
      //clear flag
       CRGFLG = CRGFLG_RTIF_MASK;
       rtiMasterCount++;
          RedLedDelayCounter++;
   }
interrupt VectorNumber_Vsci0 void RIE_ISR(void)
{   
    sci0_rxByte(&data);

    if (data == '\r') {
      
      flag = 1;
        
    }
    else 
      rx_Message[index++] = data;
   }
