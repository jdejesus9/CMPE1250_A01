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
  //EnableInterrupts;
  
/********************************************************************/
  // one-time initializations
/********************************************************************/


/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {

  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/


/********************************************************************/
// HC12 Program:  YourProg - MiniExplanation
// Processor:     MC9S12XDP512
// Bus Speed:     MHz
// Author:        This B. You
// Details:       A more detailed explanation of the program is entered here               
// Date:          Date Created
// Revision History :
//  each revision will have a date + desc. of changes



/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "lib.h"
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
unsigned int i=0;
unsigned int j=1;
unsigned int count=0;
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

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;){
if((SWL_Pushed(SWL_CTR)+SWL_Pushed(SWL_UP)+SWL_Pushed(SWL_DOWN)+SWL_Pushed(SWL_RIGHT)+SWL_Pushed(SWL_LEFT))==2)
{j=0;}
if((SWL_Pushed(SWL_CTR)+SWL_Pushed(SWL_UP)+SWL_Pushed(SWL_DOWN)+SWL_Pushed(SWL_RIGHT)+SWL_Pushed(SWL_LEFT))==3)
{j=1;}
if(j==1){
count++;}


if(SWL_Pushed(SWL_UP)){i=250;}
if(SWL_Pushed(SWL_DOWN)){i=500;}

   //0
   if(count==1){
   SWL_OFF(SWL_ALL);
   Delay_1ms(i);}
     //1
     if(count==2){
     SWL_OFF(SWL_ALL);
     SWL_ON(SWL_GREEN);
     Delay_1ms(i);}
     //2
     if(count==3){
     SWL_OFF(SWL_ALL);
     SWL_ON(SWL_YELLOW);
     Delay_1ms(i);}
     //3
     if(count==4){
     SWL_OFF(SWL_ALL);
     SWL_ON(SWL_GREEN);
     SWL_ON(SWL_YELLOW);
     Delay_1ms(i);}

     //4
     if(count==5){
     SWL_OFF(SWL_ALL);
     SWL_ON(SWL_RED);
     Delay_1ms(i);}
   
     //5
     if(count==6){
     SWL_OFF(SWL_ALL);
     SWL_ON(SWL_GREEN);
     SWL_ON(SWL_RED);
     Delay_1ms(i);}
     //6
     if(count==7){
     SWL_OFF(SWL_ALL);
     SWL_ON(SWL_RED);
     SWL_ON(SWL_YELLOW);
     Delay_1ms(i);}
     //7
     if(count==8){
     SWL_OFF(SWL_ALL);
     SWL_ON(SWL_RED);
     SWL_ON(SWL_YELLOW);
     SWL_ON(SWL_GREEN);
    Delay_1ms(i);
    count=0;}

    SWL_TOG(SWL_RED);

  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/


/********************************************************************/
// HC12 Program:  YourProg - MiniExplanation
// Processor:     MC9S12XDP512
// Bus Speed:     40 MHz
// Author:        Jackelyn
// Details:       A more detailed explanation of the program is entered here
// Date:          Date Created
// Revision History :
//  each revision will have a date + desc. of changes

/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "sw_led.h"
// Other system includes or your includes go here
// #include <stdlib.h>
// #include <stdio.h>

/********************************************************************/
// Defines
/********************************************************************/
// #define ring
/********************************************************************/
// Local Prototypes
/********************************************************************/
    //  int Helper(void);
    //  void DelayFunction(void);
    //  int Switches(void);
/********************************************************************/
// Global Variables
/********************************************************************/
// unsigned long j = 0;
/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  // Any main local variables must be declared here

  // main entry point
  _DISABLE_COP();
  // EnableInterrupts;

  /********************************************************************/
  // one-time initializations
  /********************************************************************/
  SWL_Init();

  /********************************************************************/
  // main program loop
  /********************************************************************/

  for (;;)
  {
   int pressed = Switches();

   if (pressed == 3)
   {
    SWL_ON(SWL_ALL);
   }

   if(pressed == 2)
   {
    SWL_ON(SWL_GREEN);
    SWL_OFF(SWL_YELLOW);
    SWL_OFF(SWL_RED);
   }

   if(pressed == 1)
   {
    SWL_ON(SWL_RED);
    SWL_OFF(SWL_YELLOW);
    SWL_OFF(SWL_GREEN);

   }
   if(pressed == 0)
   {
    SWL_ON(SWL_YELLOW);
    SWL_OFF(SWL_GREEN);
    SWL_OFF(SWL_RED);
   }


  }
}


/********************************************************************/
// Functions
/********************************************************************/
int Switches(void)
{
  int i = 0;
  if(SWL_Pushed(SWL_LEFT)>0) 
  {
    i++;
  }
  if(SWL_Pushed(SWL_RIGHT)>0)
  {
    i++;
  } 
  if(SWL_Pushed(SWL_UP)>0) 
  {
    i++;
  }
  if(SWL_Pushed(SWL_DOWN)>0) {
    i++;
  }
  if(SWL_Pushed(SWL_CTR)>0) {
    i++;
  }
  
  return i;
}
int Helper(void)
{

  int i = 0;

  if (SWL_Pushed(SWL_RED)>0) //if any switches on 
  {
    i++;
  }
  if (SWL_Pushed(SWL_YELLOW)>0)
  {
    i++;
  }
  if (SWL_Pushed(SWL_GREEN)>0)
  {
    i++;
  }
  
  return i;
}

void DelayFunction(void)
{
   for(j=0;j<40000;j++)
  {
        
  }

}
/********************************************************************/
// Interrupt Service Routines
/********************************************************************/



