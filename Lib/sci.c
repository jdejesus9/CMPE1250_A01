#include "derivative.h"
#include "sci.h"
#include "clock_lib.h"
unsigned long sci0_Init(unsigned long ulBaudRate, int iRDRF_Interrupt){

   static float x=0;
 
    
    SCI0CR1 = 0; // default settings work

   
    //For SCI0CR2 we need to enable transmitter and reciever
    if(iRDRF_Interrupt){
        SCI0CR2 |= SCI0CR2_TE_MASK | SCI0CR2_RE_MASK | SCI0CR2_RIE_MASK;
    }
    else
    {
          SCI0CR2 |= SCI0CR2_TE_MASK | SCI0CR2_RE_MASK;
    }
   

    //for SCI0BD, we do SBR = busspeed / (16*desired bus speed)

    x = Clock_GetBusSpeed() / (16.0*ulBaudRate);
    x += 0.5;

    SCI0BD = (unsigned int)x;

    //return Clock_GetBusSpeed() / (16.0*ulBaudRate) ;

}

// blocking byte read
// waits for a byte to arrive and returns it
unsigned char sci0_bread(void){
    unsigned char data;
    while(!(SCI0SR1 & SCI0SR1_RDRF_MASK));
    data = SCI0DRL;
  
}

// read a byte, non-blocking
// returns 1 if byte read, 0 if not
unsigned char sci0_rxByte(unsigned char * pData){
    if(SCI0SR1 & SCI0SR1_TDRE_MASK){
        *pData = SCI0DRL;
        return 1;
    }
    else{
        return 0;
    }
}

// send a byte over SCI
void sci0_txByte (unsigned char data){
    while (!(SCI0SR1 & SCI0SR1_TDRE_MASK)); // wait till transmit data register is empty
    SCI0DRL = data;
}

// send a null-terminated string over SCI
void sci0_txStr (char const * straddr){
    while(*straddr){
        sci0_txByte(*straddr);
        straddr++;
    }
}
