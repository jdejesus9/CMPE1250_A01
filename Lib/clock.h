/////////////////////////////////////////////////////////////////////////////
// Processor:     MC9S12XDP512
// Bus Speed:     16MHz (Requires Active PLL)
// Author:        Jackelyn De Jesus
// Details:       library details here
// Revision History
//      Created:  March 1st, 2024
//      each revision will have a date + desc. of changes
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// Library Prototypes
/////////////////////////////////////////////////////////////////////////////
#define DEF_BUS_CLOCK 8000000   //default clock speed

/*
    The following defines are just to avoid errors in VsCode,
    not necessary to compile and flash a program using code warrior
*/
#define EnableInterrupts   {__asm CLI;}
#define DisableInterrupts  {__asm SEI;}
#define asm _asm

//Enumeraion used for clock output / divider
typedef enum ClockDivTypedef
{                               //table 22:17
    ClockOutDiv1 = 0b00000000, //bus speed itself
    ClockOutDiv2 = 0b00000001, //bus speed divided by 2
    ClockOutDiv3 = 0b00000010, //bus speed divided by 3
    ClockOutDiv4 = 0b00000011  //bus speed divided by 4
}ClockOutDiv;


/// @brief Enable output specifying divider for it
/// @param  ClockOutDiv
void Clock_EnableOutput(ClockOutDiv external);

/// @brief Set clock to 8MHZ(default, disable pll)
/// @param  
void Clock_Set8MHZ(void); 

/// @brief Set clock to 20MHZ using PLL
/// @param  void
void Clock_Set20MHZ(void);

/// @brief Set clock to 24MHZ using PLL
/// @param void 
void Clock_Set24MHZ(void);

/// @brief Set clock to 40MHZ using PLL (optional)
/// @param void 
void Clock_Set40MHZ(void); //Set clock to 40MHZ using PLL

/// @brief Get current clock speed
/// @param  void
/// @return current BUS speed
unsigned long Clock_GetBusSpeed(void);
/////////////////////////////////////////////////////////////////////////////
// Hidden Helpers (local to implementation only)
/////////////////////////////////////////////////////////////////////////////
