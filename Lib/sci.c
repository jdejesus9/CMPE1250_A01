#include <hidef.h> 
#include "derivative.h"
#include "sci.h"

// unsigned long sci0_Init(unsigned long ulBaudRate, int iRDRF_Interrupt){

//     unsigned int baud = 200000 / (16*ulBaudRate);
//     SCI0BD = baud;

//     return baud;

// }

void sci0_Init(void){
    SCI0BD = 130;
    SCI0CR2 = 0b00001100;
}

// // blocking byte read
// // waits for a byte to arrive and returns it
// unsigned char sci0_read(void){
//     if(SCI0SR1 & SCI0SR1_RDRF_MASK){
//         *pData = SCI0DRL;
//         return 1;
//     }
//     elese {
//         return 0;
//     }
   
  
// }

// // read a byte, non-blocking
// // returns 1 if byte read, 0 if not
// // unsigned char sci0_txByte(unsigned char * pData){
    
// // }

// // send a byte over SCI
// void sci0_txByte (unsigned char data){
//     while (!(SCI0SR1 & SCI0SR1_RDRF_MASK)); // wait till transmit data register is empty
//     data = SCI0DRL;

//     if(SCI0SR1 & SCI0SR1_RDRF_MASK)
//     {
//         data = SCI0DRL;
//     }
    
// }

// // // send a null-terminated string over SCI
// // void sci0_txStr (char const * straddr){
        // for (; *straddr; ++straddr)
        //     sci0_txByte (*straddr);
// // }

// unsigned long sci0_InitMath (unsigned long ulBusClock, unsigned long ulBaudRate)
// {

// }
