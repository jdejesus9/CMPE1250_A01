#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */

#include <stdlib.h>
#include <stdio.h>

#include "segs.h"


// setup ports to speak with 7-segs

/////////////////////////////////////////////////////////////////////////////
// local helpers
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// library variables
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// constants
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// function implementations
/////////////////////////////////////////////////////////////////////////////
// static unsigned int i;

#define Segs_WLATCH     \
    PORTA &= ~(0x01);   \
    PORTA |= 0x01

#define Segs_ML PORTA &= (~0x02)
#define Segs_MH PORTA |= 0x02

void Segs_Init(void)
{
    // happen multiple times, not in init then
    // PORTB = 0b01011000; // Control byte configuration
    DDRA |= 0x03; // only happen once
    DDRB = 0xff; // only happen once
    PORTA |= 0x03; // In the notes for the init method
    Segs_Clear();   
}


// show HEX decoding (changes all of display to HEX, w/wo dp)
/* Params: (address, data, dp) */
void Segs_Normal(unsigned char Addr, unsigned char Value, Segs_DPOption dp)
{
   Addr &= 0x07;
   Addr |= 0b01011000;

   if (dp)
   {
        Value &= ~(0x80);
   }
   else{
        Value |= 0x80;
   }

   PORTB = Addr;
   Segs_MH;

   Segs_WLATCH;

   PORTB = Value;
   Segs_ML;

   Segs_WLATCH;
    // address &= (address & 0x7);
    // PORTB = (0b01011000 | address);
    // PORTA |= PORTA_PA1_MASK;
    // PORTA &= ~PORTA_PA0_MASK;
    // PORTA |= PORTA_PA0_MASK;
    // data &= 0x0F;
    // PORTB = data;

    // if (dp == Segs_DP_ON)
    // {
    //     PORTB &= ~0x80;
    // }
    // else
    // {   
    //     PORTB |= 0x80;
    // }
    // PORTA &= ~PORTA_PA1_MASK;
    // PORTA &= ~PORTA_PA0_MASK;
    // PORTA |= PORTA_PA0_MASK;

}

// control segs manually
/* Params: (address, data) */
void Segs_Custom(unsigned char Addr, unsigned char Value)
{
    Addr &= 0x07;
    
    Addr |= 0b01111000;

    PORTB = Addr;
    Segs_MH;

    Segs_WLATCH;

    PORTB = Value;
    Segs_ML;

    Segs_WLATCH;


// //(unsigned char address) see address comment at beginning for map 
// //SEGMENT ASSIGNMENT a.k.a (unsigned char data)

// //SEGBYTE=0b01111000;

//   //Port B
//   address &= (address &  0x7);
//      PORTB = (0b01111000 | address);

//   //Port A
//   PORTA |= PORTA_PA1_MASK; //Set to Control Mode
//   //LATCH
//   PORTA &= ~PORTA_PA0_MASK;
//   //Add delay for faster than 8MHZ
//   PORTA |= PORTA_PA0_MASK;

//   //Send DATA BYTE
//   //Port B

//   PORTB = data;
//   //Port A
//   PORTA &= ~PORTA_PA1_MASK; //Set to Data Mode
  
//   //LATCH
//   PORTA &= ~ PORTA_PA0_MASK;
//   //Add delay for faster than 8MHZ
//   PORTA |= PORTA_PA0_MASK;
}


// clear the display
/* Params: (address) */
// void Segs_ClearDigit(unsigned char address)
// {
//     Segs_Custom(address, 0x80);
// }

// clear the entire display
void Segs_Clear(void)
{
    int i;
    for (i = 0; i < 8; i++)
    {
        Segs_Custom(i, 0b10000000);
    }
}

// clear display upper or lower line
/* Params: (line) */
// void Segs_ClearLine(Segs_LineOption line)
// {
//     unsigned char start_addr = (line == Segs_LineTop) ? 0 : 4;
//     unsigned char end_addr = start_addr + 3;

//     for (i = start_addr; i <= end_addr; i++)
//     {
//         Segs_ClearDigit(i);
//     }
// }

void Segs_ClearLine(Segs_LineOption line)
{
    if (line == Segs_LineBottom) // bottom
    {
        Segs_Custom(4, 0b10000000); // clear bits 4-7
        Segs_Custom(5, 0b10000000);
        Segs_Custom(6, 0b10000000);
        Segs_Custom(7, 0b10000000);
    }
    else // top
    {
        Segs_Custom(0, 0b10000000); // clear bits 0-3
        Segs_Custom(1, 0b10000000);
        Segs_Custom(2, 0b10000000);
        Segs_Custom(3, 0b10000000);
    }
}

// show a 16-bit value on the upper or lower display
/* Params: (value, line) */
void Segs_16H(unsigned int value, Segs_LineOption line)
{
    byte i = 0;

    if (line == Segs_LineTop)
    {
        for (i = 0; i < 4; i++)
        {
            Segs_Normal((3 - i), (unsigned char)(value >> (i * 4)), Segs_DP_OFF);
        }
    }

    if (line == Segs_LineBottom)
    {
        for (i = 0; i < 4; i++)
        {
            Segs_Normal((7 - i), (unsigned char)(value >> (i * 4)), Segs_DP_OFF);
        }
    }
}
// show the 8-bit value starting on the digit as addr (0-6)
/* Params: (addr, value) */
void Segs_8H(unsigned char Addr, unsigned char Value)
{
    unsigned char hChar, lChar;

    Addr &= 0x7;
    hChar = Value >> 4;
    lChar = Value & 0x0F;

    Segs_Normal (Addr, hChar, Segs_DP_OFF);

    if (Addr < 7)
    {
        Segs_Normal(Addr + 1, lChar, Segs_DP_OFF);
    }
    else{
        Segs_Normal(0, lChar, Segs_DP_OFF);
    }
    // if (value > 255)
    // {
    //     value = 0;
    // }

    // if (value > 15)
    // {
    //     address &= 6;
    //     Segs_Normal(address, ((value >> 4) & (0x0F)), Segs_DP_OFF);
    //     Segs_Normal(address + 1, ((value) & (0x0F)), Segs_DP_OFF);
    // }
    // else
    // {
    //     address &= 7;
    //     Segs_Normal(address, (value & (0x0F)), Segs_DP_OFF);
    // }
}


// say Err on the appropriate line
/* Params: (line) */

// void Segs_SayErr(Segs_LineOption line)
// {
//     unsigned char startAddr = (line == Segs_LineTop) ? 0 : 4;
    
//     Segs_Custom(startAddr, 'E');
//     startAddr++;

//     // Display 'r' (segments A and F)
//     Segs_Custom(startAddr, 'r');
//     startAddr++;

//     // Display 'r' (segments A and F)
//     Segs_Custom(startAddr, 'r');
// }


// // show a decimal value on the first or second line of the 7-segs
// /* Params: (value, line) */
void Segs_16D(unsigned int value, Segs_LineOption line)
{
    byte i = 0;
    if (value > 9999)
    {
        value = 0;
    }
    if (line == Segs_LineTop)
    {
        for (i = 0; i < 4; i++)
        {
            Segs_Normal(3 - i, value % 10, Segs_DP_OFF);
            value /= 10;
        }
    }
    else if (line == Segs_LineBottom)
    {
        for (i = 0; i < 4; i++)
        {
            Segs_Normal(7 - i, value % 10, Segs_DP_OFF);
            value /= 10;
        }
    }
}


// int Segs_IncrementOnDecimal(unsigned int decimalPlace, unsigned int incrementValue, unsigned int number)
// {
//      // Needed, can adjust manually if need
//     int divisor[] = {1000, 100, 10, 1};

//     // may need a div for all values later on

//     int digit = (number / divisor[decimalPlace]) % 10; // Get the value as digit

//     digit + incrementValue; // Increments the digit

//     digit = (digit + 10) % 10; // Wraps digit value back using modulo (0-9 range)

//     // Update the number with the new digit value

//     number = number - ((number / divisor[decimalPlace]) % 10) * divisor[decimalPlace] + digit * divisor[decimalPlace];

//     return number;
// }
// // void LATCH()
// // {
// //     PORTA &= ~PORTA_PA0_MASK;
// //     PORTA |= PORTA_PA0_MASK;
// // }

// // void DATAMODE()
// // {
// //     PORTA &= ~PORTA_PA1_MASK;
// // }

// // void CONTROLMODE()
// // {
// //     PORTA |= PORTA_PA1_MASK;
// // }