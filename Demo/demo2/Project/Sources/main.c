/********************************************************************/
// HC12 Program:  YourProg - MiniExplanation
// Processor:     MC9S12XDP512
// Bus Speed:     40MHz
// Author:        JACKELYN DE JESUS
// Details:       A more detailed explanation of the program is entered here               
// Date:          Date Created
// Revision History :
//  each revision will have a date + desc. of changes



// /********************************************************************/
// // Library includes
// /********************************************************************/
// #include <hidef.h>      /* common defines and macros */
// #include "derivative.h" /* derivative-specific definitions */

// //Other system includes or your includes go here
// //#include <stdlib.h>
// //#include <stdio.h>


// /********************************************************************/
// //Defines
// /********************************************************************/

// /********************************************************************/
// // Local Prototypes
// /********************************************************************/

// /********************************************************************/
// // Global Variables
// /********************************************************************/

// /********************************************************************/
// // Constants
// /********************************************************************/

// /********************************************************************/
// // Main Entry
// /********************************************************************/
// void main(void)
// {
//   //Any main local variables must be declared here

//   // main entry point
//   _DISABLE_COP();
//   EnableInterrupts;
  
// /********************************************************************/
//   // one-time initializations
// /********************************************************************/
// PLL_To20MHz();
// SWL_Init();
// Segs_Init();
// // do SCI startups
// SCI0BD = 130; // 20E6 / (9600 * 16) // 11.3.2.1
 
// SCI0CR2 = 0b00001100; // turn on TX/RX // 11.3.2.6

// /********************************************************************/
//   // main program loop
// /********************************************************************/

//   for (;;)
//   {
//   // if the transmitter buffer is empty, load a new byte to send (TX)
//   if (SCI0SR1_TDRE /*&& SWL_Transition (SWL_CTR)*/)
//   SCI0DRL = rand() % 26 + 'A';
//   // if a byte has been received, pull it!
//   if (SCI0SR1_RDRF)
//   Segs_8H (2, SCI0DRL);

//   }                   
// }

// /********************************************************************/
// // Functions
// /********************************************************************/

// /********************************************************************/
// // Interrupt Service Routines
// /********************************************************************/



/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */

//Other system includes or your includes go here
//#include <stdlib.h>
#include <stdio.h>

#include "segs.h"
#include "sw_led.h"
#include "clock.h"
#include "rti.h"
#include "lcd.h"
#include "sci.h"


/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
char Name[] = "j. dejesus";
unsigned int counter1 = 0;
unsigned char incCounter1 = 0;
unsigned char message[50];

SwState centerState;  //Question 5 
unsigned char swtPressed = 0; //Question 5

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
SWL_Init();
Clock_Set20MHZ();
// PIT_InitChannel(PIT_CH0, PIT_MT0, PIT_IDIS);
//   PITMTLD0 = 25-1;
//   PITLD0 = 50000-1;

// PIT_Start(); //required for lcd
lcd_Init();

//write the string
//Question 1
lcd_StringXY(20-12, 3, Name);
Segs_Init(); 
Segs_16D(counter1, Segs_LineTop); 

//Question 4
(void)sprintf(message, "DEC: %04u", counter1);
lcd_StringXY(0,0,message); 
(void)memset(message,0,sizeof(message));


(void)sprintf(message, "HEX: %04x", counter1);
lcd_StringXY(0,1,message); 
(void)memset(message,0,sizeof(message));  

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
      //Question 2
      /*
      if(PITTF_PTF0)
      {
        //clear the flag 
        PITTF = PITTF_PTF0_MASK; 
        SWL_TOG(SWL_RED); //TOGGLE GREEN 

        ++incCounter1;   
      }*/

      //Question 3
      if(incCounter1>=8 && !swtPressed)
      {
        incCounter1 = 0; //reset variable 
        
        ++counter1; 
        
        if(counter1>9999)
          counter1 = 0; 
        
        //Question 4
        //update the display 
        Segs_16D(counter1, Segs_LineTop);

        (void)sprintf(message, "DEC: %04u", counter1);
        lcd_StringXY(0,0,message); 
        (void)memset(message,0,sizeof(message));

        (void)sprintf(message, "HEX: %04x", counter1);
        lcd_StringXY(0,1,message); 
        (void)memset(message,0,sizeof(message));   


        //Question 5
      }
      if(Sw_ProcessD(&centerState, SWL_CTR) == Pressed)
      {
        swtPressed= 1; 
        (void)sprintf(message, "DEC: %04u", counter1);
        lcd_StringXY(0,0,message); 
        (void)memset(message,0,sizeof(message));

        (void)sprintf(message, "HEX: %04x", counter1);
        lcd_StringXY(0,1,message); 
        (void)memset(message,0,sizeof(message));   


      }
        if(Sw_ProcessD(&centerState, SWL_CTR) == Pressed)
        {
          swtPressed = 0;
        (void)sprintf(message, "DEC: %04u", counter1);
        lcd_StringXY(0,0,message); 
        (void)memset(message,0,sizeof(message));

        (void)sprintf(message, "HEX: %04x", counter1);
        lcd_StringXY(0,1,message); 
        (void)memset(message,0,sizeof(message));
        }

  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
interrupt VectorNumber_Vpit0 void PIT0_ISR(void)
{
        //Question 2
      if(PITTF_PTF0)
      {
        //clear the flag 
        PITTF = PITTF_PTF0_MASK; 
        SWL_TOG(SWL_RED); //TOGGLE GREEN 

        ++incCounter1;   
      }
}