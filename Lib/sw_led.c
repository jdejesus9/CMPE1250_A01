#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */

#include "sw_led.h" // on includes when implemented
//#include "pit.h
// other includes, as *required* for this implementation

/////////////////////////////////////////////////////////////////////////////
// local prototypes
/////////////////////////////////////////////////////////////////////////////
static SwState state = Idle;
static unsigned int debounceCounter = 0;
#define DEBOUNCE_DELAY 5 // Adjust this value based on your requirements
/////////////////////////////////////////////////////////////////////////////
// library variables
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// constants
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// function implementations
/////////////////////////////////////////////////////////////////////////////
// init - must be called to init port PT1AD1
void SWL_Init (void){
PT1AD1 = 0b00011111; //initial condition only time I assign a value. In the infinite loop - bitwise operations
DDR1AD1 = 0b11100000; //1 for output and 0 for input 
ATD1DIEN1 = 0b00011111; //enable inputs
}

///////////////////////////////////////////////////////////////
// LED functions
void SWL_ON (SWL_LEDColour led){
 PT1AD1 |= led;
}
void SWL_OFF (SWL_LEDColour led){
PT1AD1 &= ~led;
}
void SWL_TOG (SWL_LEDColour led){
PT1AD1 ^= led;
}
///////////////////////////////////////////////////////////////
// special LED function
//void SWL_AUX_ON (void);
//void SWL_AUX_OFF(void);

///////////////////////////////////////////////////////////////
// switch functions

// is a specific switch being pushed (T/F)
int SWL_Pushed (SWL_SwitchPos pos){
if (PT1AD1 & pos)
{

 return 1;
   
}
else
{
    return 0 ;
 }

}

// is any switch being pushed (T/F)

int SWL_Any (void){
    return(PT1AD1 & SWL_ALL);
}
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// you won't implement these function initially
// after we talk about some switch related issues, you will be
//  implementing these functions

// by switch name
// int SWL_PushedDeb (SWL_SwitchPos pos)  //Debounced version of SWL_Pushed
// {

//     unsigned int i;
//     if (PT1AD1 & pos)
//     {
//         i = 1;
//     }
//     else
//     {
//         i = 0;
//     }

//     /*PIT_Sleep(PIT_CH0, 1);
//     if (PT1AD1 & pos)
//     {
//         i = 1;
//     }
//     else{
//         i = 0;
//     }
//     return i; */

    
//     Process the switch state
//     switch (Sw_Process(&state, pos)) {
//         case Pressed:
//             debounceCounter++;
//             if (debounceCounter >= DEBOUNCE_DELAY) {
//                 debounceCounter = 0;
//                 return 1; // Switch is considered pressed after debounce delay
//             }
//             break;

//         case Released:
//             debounceCounter = 0;
//             break;

//         default:
//             break;
//     }

//     return 0; // Switch is not pressed

// }
// //Optional - Using 
// SwState Sw_Process(SwState *state, SWL_SwitchPos sw_pos)//Process state of a swicth in PT1AD1
// {
//     if (SWL_Pushed(sw_pos))
//     {
//         //Active
//         if(*state == Idle)
//         {
//             *state = Pressed;
//         }
//         else
//         {
//             *state = Held;
//         }
//     }
//     else
//     {

//         //Inactive
//         if(*state == Held)
//         {
//             *state = Released;
//         }
//         else
//         {
//             *state = Idle;
//         }
        

//     }

//     return *state;
// } 
// //Process debounced state of a swicth in PT1AD1
// SwState Sw_ProcessD(SwState *SState, SWL_SwitchPos SPos) //port, SwState, PIN
// {
//     if(SWL_PushedDeb(SPos))
//     {
//          //Active
//         if(*SState == Idle)
//         {
//             *SState  = Pressed;
//         }
//         else
//         {
//             *SState  = Held;
//         }
//     }
//         else
//     {

//         //Inactive
//         if(*SState == Held)
//         {
//             *SState = Released;
//         }
//         else
//         {
//             *SState = Idle;
//         }
        

//     }
//     return *SState;
// }

////////////////////////////////////////////////////////////////////////////
// Hidden Helpers (local to implementation only)
/////////////////////////////////////////////////////////////////////////////

