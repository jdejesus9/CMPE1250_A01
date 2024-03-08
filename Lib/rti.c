#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "rti.h"

void RTI_Init(void){
    //CRGINT |= CRGINT_RTIE_MASK; //0b10000000, Enable RTI
    RTICTL = 0b10010111;
}

void RTI_Delay_ms(unsigned int ms){
    //Decimal, divider 2000, mod8 counter -> 1ms
  rtiMasterCount=0;   //rti counter

  //RTICTL = 0;   //OFF

  //RTICTL = 0b10010111;    //ON

  CRGFLG = CRGFLG_RTIF_MASK;

  while (ms > rtiMasterCount){
    if (CRGFLG_RTIF)
      {
        CRGFLG = CRGFLG_RTIF_MASK;
        rtiMasterCount++;
      }
  }
  //RTICTL = 0;

}