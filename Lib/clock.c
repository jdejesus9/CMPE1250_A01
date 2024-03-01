#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */

#include "clock.h"

// other includes, as *required* for this implementation

/////////////////////////////////////////////////////////////////////////////
// local prototypes
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// library variables
/////////////////////////////////////////////////////////////////////////////
unsigned long clockSpeed = DEF_BUS_CLOCK;
/////////////////////////////////////////////////////////////////////////////
// constants
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// function implementations
/////////////////////////////////////////////////////////////////////////////

    /// @brief Enable output specifying divider for it
/// @param  ClockOutDiv
// void Clock_EnableOutput(ClockOutDiv clockDiv)
// {
//     ECLKCTL &= ~ECLKCTL_NECLK_MASK; //Activate clock output
//     ECLKCTL |= clockDiv;

//     if(external == ClockOutDiv1)
//     {
//         return; //clock divide by 1    71429 = 500ms
//     }
//     else if(external == ClockOutDiv2 )
//     {
//         ECLKCTL |= ECLKCTL_EDIV0_MASK; //clock divide by 2
//     }
//     else if(external == ClockOutDiv3)
//     {
//         ECLKCTL |= ECLKCTL_EDIV1_MASK;//clock divide by 3
//     }
//     if(external == ClockOutDiv4)
//     {
//         ECLKCTL |= ECLKCTL_EDIV1_MASK | ECLKCTL_EDIV0_MASK; //clock divide by 4
//     }

// }
/// @brief Set clock to 8MHZ(default, disable pll)
/// @param  
void Clock_Set8MHZ(void)
{
    ECLKCTL &= ~CLKSEL_PLLSEL_MASK;
    DEF_BUS_CLOCK;
    clockSpeed = DEF_BUS_CLOCK;

}



/// @brief Set clock to 20MHZ using PLL
/// @param  void
void Clock_Set20MHZ(void)
{

 SYNR = 4;
 REFDV = 3;

 PLLCTL |= PLLCTL_PLLON_MASK | PLLCTL_AUTO_MASK; 

 while (!(CRGFLG & CRGFLG_LOCK_MASK)); 
 
 CLKSEL |= CLKSEL_PLLSEL_MASK;
 clockSpeed = 20000000; //set clock to 20MHz using PLL
}

/// @brief Set clock to 24MHZ using PLL
/// @param void 
void Clock_Set24MHZ(void)
{
 SYNR = 2;
 REFDV = 1;

 PLLCTL |= PLLCTL_PLLON_MASK | PLLCTL_AUTO_MASK; 

 while (!(CRGFLG & CRGFLG_LOCK_MASK)); 
 
 CLKSEL |= CLKSEL_PLLSEL_MASK;
 clockSpeed = 24000000; //set clock to 24MHz using PLL

}

/// @brief Set clock to 40MHZ using PLL (optional)
/// @param void 
void Clock_Set40MHZ(void)
{
    SYNR = 4;
    REFDV = 1;

 PLLCTL |= PLLCTL_PLLON_MASK | PLLCTL_AUTO_MASK; 

 while (!(CRGFLG & CRGFLG_LOCK_MASK)); 
 
 CLKSEL |= CLKSEL_PLLSEL_MASK;
 clockSpeed = 40000000; //set clock to 40MHz using PLL
}

/// @brief Get current clock speed
/// @param  void
/// @return current BUS speed
unsigned long Clock_GetBusSpeed(void)
{
    return clockSpeed;
}