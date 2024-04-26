/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "lcd.h"
#include "sw_led.h"
#include "segs.h"
#include "clock.h"
//#include "rti.h"
//Other system includes or your includes go here
#include <stdlib.h>
//#include <stdio.h>



/********************************************************************/
//Defines
/********************************************************************/
#define MAX_ROWS 2  // Adjust based on your LCD configuration (commonly 2 or 4)
#define MAX_COLS 16 // Adjust based on your LCD configuration (commonly 16 or 20)
/********************************************************************/
// Local Prototypes
/********************************************************************/
    unsigned int depositedCharacters = 0;
    unsigned char cursorVisible = 1;  // Cursor initially visible
    unsigned char cursorBlink = 0;    // Cursor initially does not blink
    unsigned char cursorX = 0;
    unsigned char cursorY = 0;

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
    

  // main entry point
  _DISABLE_COP();
 //EnableInterrupts;
   
  
/********************************************************************/
  // one-time initializations
/********************************************************************/
    // Initialize all libraries
    lcd_Init();
    SWL_Init();
    Segs_Init();
    //Clock_Set20MHZ();  // Set clock to 20MHz using PLL

    //RTI_Delay_ms(50);
    Segs_16D(depositedCharacters, Segs_LineTop);
    
    SwState upState;
  SwState downState;
  SwState rightState;
  SwState leftState;


/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
      while (lcd_Busy()){
            // Set cursor visibility and blink state based on switch inputs
        //lcd_DispControl(cursorVisible, cursorBlink);
               // Display the number of deposited characters on the upper line of the 7-segs in decimal
        Segs_16D(depositedCharacters, Segs_LineTop);

        // Check switch transitions
        if (SWL_PushedDeb(SWL_UP)) {
              if (cursorY > 0) {
                cursorY--;
                lcd_AddrXY(cursorX, cursorY);
    }
        }
        if (SWL_PushedDeb(SWL_LEFT)) {
              if (cursorX > 0) {
                    cursorX--;
                    lcd_AddrXY(cursorX, cursorY);
                }
        }
        if (SWL_PushedDeb(SWL_RIGHT)) {
                if (cursorY < MAX_ROWS - 1) {
                    cursorY++;
                    lcd_AddrXY(cursorX, cursorY);
                }
        }
        if (SWL_PushedDeb(SWL_DOWN)) {
              if (cursorX < MAX_COLS - 1) {
                    cursorX++;
                    lcd_AddrXY(cursorX, cursorY);
                }
        }
        if (SWL_PushedDeb(SWL_CTR)) {
            // Deposit a random character in the range of 'A' to 'Z'
            char randomChar = 'A' + rand() % 26;
            lcd_StringXY(0, 0, &randomChar);

            // Increment deposited character count
            depositedCharacters++;

            // Check if the program state needs to be fully reset
            if (depositedCharacters == 15) {
                lcd_Clear();
                lcd_Home();
                depositedCharacters = 0;
            }

            // Blink the red LED for 50ms
            SWL_ON(SWL_RED);
            //PIT_Sleep(PIT_CH0, 50);
            //RTI_Delay_ms(50);
            SWL_OFF(SWL_RED);
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
