/********************************************************************/
// HC12 Program:  LAB03 - Number Entry / HEX Converter
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

//Other system includes or your includes go here
#include <stdlib.h>
#include <stdio.h>

#include "sw_led.h"
#include "segs.h"
#include "sci.h"
#include "pll.h"
#include "clock.h"


/********************************************************************/
//Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/
unsigned int count=0;

unsigned int index=0;
unsigned int toUpdateData;

unsigned int num0=0;
unsigned int num1=0;
unsigned int num2=0;
unsigned int num3=0;

unsigned char data;
Seg16Typedef num; 
unsigned int deccount=0;

SwState upState;
SwState downState;
SwState rightState;
SwState leftState;
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
Segs_Init();

num.Nibble.Nibble3=0;
num.Nibble.Nibble2=0;
num.Nibble.Nibble1=0;
num.Nibble.Nibble0=0;

/********************************************************************/
  // main program loop
/********************************************************************/

  for (;;)
  {
    if(Sw_Process(&leftState,SWL_LEFT)==Released)
      {PT1AD1 &= 0b00011111; 
    if(++index>3){index=3;}
      }
    if(Sw_Process(&rightState,SWL_RIGHT)==Released)
      {PT1AD1 &= 0b00011111; 
    if(--index<0||index>3){index=0;}
      }
    if(Sw_Process(&upState,SWL_UP)==Released)
      {PT1AD1 &= 0b00011111; 
    updateNum(index,1);
      }
    if(Sw_Process(&downState,SWL_DOWN)==Released)
      {PT1AD1 &= 0b00011111; 
    updateNum(index,-1);
      }   

    Segs_ClearLine(Segs_LineTop);
      
    update(index);
    updateData(toUpdateData);
      
    Segs_16H(num.Word,Segs_LineTop);
    Segs_Custom(3-index,0x0|data);

    num0=num.Nibble.Nibble0;
    num1=num.Nibble.Nibble1;
    num2=num.Nibble.Nibble2;
    num3= num.Nibble.Nibble3;

    deccount=1000*num.Nibble.Nibble3+100*num.Nibble.Nibble2+10*num.Nibble.Nibble1+num.Nibble.Nibble0;
    Segs_16H(deccount,Segs_LineBottom);
    
    count=0;    // reset the counter

  }                   
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
int updateData(unsigned int number )
{
  switch (number)
  {
  case 1:data= SEG_C| SEG_B;
    break;

  case 2:data= SEG_A| SEG_B| SEG_G| SEG_D| SEG_E;
    break;
  
  case 3:data= SEG_A| SEG_B| SEG_G| SEG_D| SEG_C;
    break;
  
  case 4:data= SEG_F| SEG_B| SEG_G| SEG_C;
    break;
  
  case 5:data= SEG_A| SEG_G| SEG_D| SEG_C| SEG_F;
    break;
  
  case 6:data= SEG_A| SEG_B| SEG_G| SEG_D| SEG_E| SEG_C;
    break;
  
  case 7:data= SEG_A| SEG_B| SEG_C;
    break;
  
  case 8:data= SEG_A| SEG_B| SEG_G| SEG_D| SEG_E| SEG_C| SEG_F;
    break;
  
  case 9:data= SEG_A| SEG_B| SEG_G| SEG_D| SEG_C| SEG_F;
    break;

  case 0:data= SEG_A| SEG_B| SEG_D| SEG_E| SEG_C| SEG_F;
    break;

  default:
    break;
  }
}
int updateNum(unsigned int ind,unsigned int change)
{
  switch (ind)
  {
  case 0: 
    if(num.Nibble.Nibble0==0 && change==-1)
    {num.Nibble.Nibble0=9;}
   else{  num.Nibble.Nibble0 += change;
          if(num.Nibble.Nibble0>9&&num.Nibble.Nibble0<60000)
          {num.Nibble.Nibble0=0;}
       }       
    break;

  case 1:
    if(num.Nibble.Nibble1==0 && change==-1)
      {num.Nibble.Nibble1=9;}
  else
    {num.Nibble.Nibble1 += change;
      if(num.Nibble.Nibble1>9&&num.Nibble.Nibble1<60000)
      {num.Nibble.Nibble1=0;}
    }   
    break;
  
  case 2:
    if(num.Nibble.Nibble2==0 && change==-1)
      {num.Nibble.Nibble2=9;}
  else
      {num.Nibble.Nibble2 += change;
        if(num.Nibble.Nibble2>9&&num.Nibble.Nibble2<60000)
        {num.Nibble.Nibble2=0;}
      }   
    break;
  
  case 3:
    if(num.Nibble.Nibble3==0 && change==-1)
        {num.Nibble.Nibble3=9;}
  else
    {num.Nibble.Nibble3 += change;
      if(num.Nibble.Nibble3>9&&num.Nibble.Nibble3<60000)
        {num.Nibble.Nibble3=0;}
    }  
    break;  
  
  default:
    break;
  }
}
int update(unsigned int ind)
{
  switch (ind)
  {
  case 0: toUpdateData=num.Nibble.Nibble0;
    break;

  case 1: toUpdateData=num.Nibble.Nibble1;
    break;
  
  case 2: toUpdateData=num.Nibble.Nibble2;
    break;
  
  case 3: toUpdateData=num.Nibble.Nibble3;
    break;
  
  default:
    break;
  }
}