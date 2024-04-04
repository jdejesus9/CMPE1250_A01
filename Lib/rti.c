extern volatile unsigned long rtiMasterCount;

#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "rti.h"

/*void RTI_Init(void){
    //CRGINT |= CRGINT_RTIE_MASK; //0b10000000, Enable RTI
    RTICTL = 0b10010111;
}

void RTI_Delay_ms(unsigned int ms){
    //Decimal, divider 2000, mod8 counter -> 1ms
  //rtiMasterCount=0;   //rti counter

  RTICTL = 0;   //OFF

  RTICTL = 0b10010111;    //ON

  CRGFLG = CRGFLG_RTIF_MASK;

  while (ms > 0){
    if (CRGFLG_RTIF)
      {
        CRGFLG = CRGFLG_RTIF_MASK;
        ms--;
      }
  }
  RTICTL = 0;

}*/


unsigned int count = 2660;
/////////////////////////////////////////////////////////////////////////////
// constants
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// function implementations
/////////////////////////////////////////////////////////////////////////////

    /// brief Enables RTI Moule
/// param  
void RTI_Init(void){
    CRGINT |= CRGINT_RTIE_MASK; //0b10000000, Enable RTI
    RTICTL = 0b10010111;
}

/// //brief Enables RTI Module with callback to be used in main
/// param function 
/*
We will implemente this function later once we cover 
function pointers
*/
//void RTI_InitCallback(void(*function)(void));

/// brief Blocking delay to be used  once the RTI MOdule is enabled
/// param timeout 
void RTI_Delay_ms(unsigned int ms){
    //Decimal, divider 2000, mod8 counter -> 1ms
  unsigned int i;
  unsigned int loop;
  
  for(i=0;i<ms;i++)
  {
    loop=2660;
    while(--loop);
  }

}