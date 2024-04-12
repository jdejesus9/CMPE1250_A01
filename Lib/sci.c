#include <hidef.h> 
#include "derivative.h"
#include "sci.h"
#include "sw_led.h"
#include "pll.h"

#include <stdlib.h>
#include <stdio.h>


void sci0_Init(unsigned long ulBaudRate, int iRDRF_Interrupt){

    unsigned long baud = 20000000 / (16 * ulBaudRate);
    SCI0BD = baud;

    // return baud;

}

// void sci0_Init(void){
//     SCI0BD = 130;
//     SCI0CR2 = 0b00001100;
// }

// blocking byte read
// waits for a byte to arrive and returns it
// unsigned char sci0_read(unsigned char * pData){
    
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
void sci0_txByte (unsigned char data){
    while (!(SCI0SR1 & SCI0SR1_RDRF_MASK)); // wait till transmit data register is empty
    SCI0DRL = data;

    // if(SCI0SR1 & SCI0SR1_RDRF_MASK)
    // {
    //     data = SCI0DRL;
    // }
    
}

unsigned int sci0_rxByte(unsigned char * pData){
    if(SCI0SR1 & SCI0SR1_RDRF_MASK){
        *pData = SCI0DRL;
        return 1;
    }
    else{
        return 0;
    }
}

// send a null-terminated string over SCI
void sci0_txStr (char const * straddr){
        for (; *straddr; ++straddr)
            sci0_txByte (*straddr);
}

void sci0_InitMath (unsigned long ulBusClock, unsigned long ulBaudRate)
{
    unsigned long baud = ulBusClock / (16*ulBaudRate);
    SCI0BD = baud;

    // return baud;

}



// return 1 if RDRF set, otherwise return 0
int sci0_Peek (void)
{
    if (SCI0SR1_RDRF)
    {
        return 1;
    }
    else{
        return 0;
    }

}

// // use an escape sequence to place the cursor at the specified position
// // this is the \x1B[y;xH form with formatted argument replacement (sprintf)
// void sci0_GotoXY (int iCol, int iRow)
// {

// }

// // use sci0_GotoXY and sci0_txStr to place the string
// void sci0_txStrXY (int iCol, int iRow, char const * straddr)
// {

// }

// // use an escape sequence to clear the terminal
void sci0_ClearScreen ()
{
    sci0_txStr("\x1b[1J");
}

// // output 1s and 0s to display a 16-bit value
// // as binary on the SCI at the current position
void sci0_ShowBin16 (unsigned int iVal)
{
    int decinum, binarynum[32], x;
        printf("Please enter a decimal number: ");
        scanf("%d", &decinum);

    for (x = 0; decinum > 0; x++)
    {
        binarynum[x] = decinum % 2;
        decinum = decinum / 2;
    }
    printf("Binary representation is: ");
    for (x = x - 1; x >= 0; x--)
    {
        printf("%d", binarynum[x]);
    }

}

// // take a single ASCII character that looks like HEX and
// // convert it to the numerical equivalent
// // valid characters are '0'-'9', 'a'-'f', 'A'-'F'
// // all other ASCII codes return 0
// int ToDigitVal (char digit)
// {

// }

// // convert the 4 character ASCII array representation
// // into a single 16-bit value
// // uses ToDigitVal to convert each position
// unsigned int HexArrayToUInt16 (char * pArray)
// {

// }

// // draw the entire portion of the output that changes
// // with a change in operands or operator
// void DrawState (unsigned int iOPA, unsigned int iOPB, Operation op)
// {

// }

// // cursor needs to go back to editing position
// sci0_GotoXY (13 + iXEditPos, 5 + iYEditPos)
// {

// }



/*#include "derivative.h"
#include "sci.h"
#include "clock.h"
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
}*/








