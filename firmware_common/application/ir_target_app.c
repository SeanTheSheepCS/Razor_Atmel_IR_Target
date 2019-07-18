/*!*********************************************************************************************************************
@file ir_target_app.c
@brief Responsible for:
          -flashing lights and turning on buzzer if the IR reciever recieves a signal
------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void IrTargetInitialize(void);
- void IrTargetRunActiveState(void);

- static void IrGateSM_Idle(void);
- static void IrGateSM_SignalDetected(void);


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>IRTarget"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32IrTargetFlags;                          /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */
extern volatile u32 G_u32ApplicationFlags;                /*!< @brief From main.c */

/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "IrTarget_<type>" and be declared as static.
***********************************************************************************************************************/
static fnCode_type IrTarget_pfStateMachine;               /*!< @brief The state machine function pointer */
static u32 IrTarget_u32Timeout;                           /*!< @brief Timeout counter used across states */

/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */
/*--------------------------------------------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------------------------------------------------
Function:

Description:

Requires:
  -

Promises:
  -
*/
void IrTargetInitialize(void)
{
  LCDCommand(LCD_CLEAR_CMD);
  LCDMessage(LINE1_START_ADDR, "IR_TARGET");
  IrTarget_pfStateMachine = IrTargetSM_Idle;
} /* end IrTargetInitialize() */


/*----------------------------------------------------------------------------------------------------------------------
Function:

Description:

Requires:
  -

Promises:
  -

*/
void IrTargetRunActiveState(void)
{
  IrTarget_pfStateMachine();

} /* end IrTargetRunActiveState */

/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/
/*-------------------------------------------------------------------------------------------------------------------*/
/* In this state...
 *
 */
static void IrTargetSM_Idle(void)
{
  if(IsPinActive(INPUT_PIN_UPIMO))
  {
    LedOn(WHITE);
    LedOn(PURPLE);
    LedOn(BLUE);
    LedOn(CYAN);
    LedOn(GREEN);
    LedOn(YELLOW);
    LedOn(ORANGE);
    LedOn(RED);
    IrTarget_pfStateMachine = IrTargetSM_SignalDetected;
  }
} /* end IRTargetSM_Idle() */

/*-------------------------------------------------------------------------------------------------------------------*/
/* Increments the timer, stops if BUTTON0 is pressed, other behavoir depends on mode, please check extra_information/the_different_modes.txt */
static void IrTargetSM_SignalDetected(void)
{
  if(!IsPinActive(INPUT_PIN_UPIMO))
  {
    LedOff(WHITE);
    LedOff(PURPLE);
    LedOff(BLUE);
    LedOff(CYAN);
    LedOff(GREEN);
    LedOff(YELLOW);
    LedOff(ORANGE);
    LedOff(RED);
    IrTarget_pfStateMachine = IrTargetSM_Idle;
  }
} /* end IrTargetSM_SignalDetected() */

/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
