/********************************************************************/
// HC12 Program:  YourProg - MiniExplanation
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
#include "sci.h"
#include "rti.h"
#include "sw_led.h"
#include "clock.h"


//Other system includes or your includes go here
//#include <stdlib.h>
#include <stdio.h>


/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/
interrupt VectorNumber_Vrti void RTI_1ms (void);
/********************************************************************/
// Global Variables
/********************************************************************/
int delay = 50;
SwState ctrState, upState, downState, leftState, rightState;
unsigned char rxData;
char empty[20];
unsigned int i = 0;
int index;
int Parse;
int ParsedInt;
char formattedMessage[50]; //this is for formatting the ms in the message later on.
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
    RTI_Init();
    (void) sci0_Init(115200, 0); // Enable RDRF interrupts
    Clock_Set20MHZ();
   
    sci0_txStr("\x1b[2J");      //Clear entire screen
    sci0_txStr("\x1b[0;0H");    //Go Home

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
     
    //Part A
    if(rtiMasterCount >= delay){ //if rtiMaster count = 50ms since it increments every 1ms
      SWL_TOG(SWL_RED);
      rtiMasterCount = 0; //reset the rti Master count
    }

     //Part B
      if(Sw_Process(&upState, SWL_UP) == Pressed)
      {
        if(delay >= 100){
          delay = 100; //if delay is already at 100, then keep it at 100
        }
        else{
            delay += 10; // adds 10 to the delay if the if statements above are not true
        }
      }

      if(Sw_Process(&downState,SWL_DOWN)==Pressed){
        if(delay <= 10){
          delay = 10;
        }
        else{
          delay -= 10; //subtracts 10 if the delay is not already at the minimum value of 10
        }
      
      
      }

      //Part C
    if (SCI0SR1_RDRF)
    {
    if(sci0_rxByte(&rxData))
    {
      
      empty[i] = rxData;
      i++;

      if(rxData == 13) { //if Enter is hit
        //sci0_txStr(empty); these were just test codes
        sci0_txStr("\n\r"); //so that it enters a new line in tera term

        Parse = sscanf(empty, "%d", &ParsedInt);

         if(Parse==0) {
            sci0_txStr("Input wrong format.\n\r");
          }
        else if(ParsedInt > 100 || ParsedInt < 10){
            sci0_txStr("Wrong Setting, number must be between 10 and 100 inclusive.\n\r");

        }
        else{
          sprintf(formattedMessage, "RTI event set to %dms\n\r", ParsedInt);
          sci0_txStr(formattedMessage);
          delay = ParsedInt;
        }

        for(index = 0; index < 20; index++) { // Clear the array after Enter
            empty[index] = '\0';
            i=0; //need to reset after clearing
        }
      }
      //send it back to the sci
      sci0_txByte(rxData);
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
interrupt VectorNumber_Vrti void RTI_1ms (void)
{
 CRGFLG = CRGFLG_RTIF_MASK; //clear flag;
 //Perform some action here
  //Part 1

  rtiMasterCount++;


}
