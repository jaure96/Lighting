#ifndef visualSTATE_LIGHTINGSYSTEM_H
#define visualSTATE_LIGHTINGSYSTEM_H

/*
 * Id:        LightingSystem.h
 *
 * Function:  Contains definitions needed for API functions.
 *
 * This is an automatically generated file. It will be overwritten by the Coder.
 * 
 * DO NOT EDIT THE FILE!
 */


#include "Lighting.h"


/*
 * Number of Identifiers.
 */
#define VS_NOF_ACTION_FUNCTIONS          3U
#define VS_NOF_EVENTS                    4U
#define VS_NOF_INSTANCES                 1U
#define VS_NOF_STATE_MACHINES            1U
#define VS_NOF_STATES                    3U


/*
 * Undefined State.
 */
#define STATE_UNDEFINED                  255U


/*
 * Undefined Event.
 */
#define EVENT_UNDEFINED                  255U


/*
 * Undefined Event Group.
 */
#define EVENT_GROUP_UNDEFINED            255U


/*
 * Event Termination ID.
 */
#define EVENT_TERMINATION_ID             255U


/*
 * SEM Variable Types.
 */
typedef VS_UINT8  SEM_EVENT_TYPE;
typedef VS_UINT8  SEM_ACTION_EXPRESSION_TYPE;
typedef VS_UINT8  SEM_GUARD_EXPRESSION_TYPE;
typedef VS_UINT8  SEM_EXPLANATION_TYPE;
typedef VS_UINT8  SEM_STATE_TYPE;
typedef VS_UINT8  SEM_STATE_MACHINE_TYPE;
typedef VS_UINT8  SEM_INSTANCE_TYPE;
typedef VS_UINT8  SEM_SIGNAL_QUEUE_TYPE;
typedef VS_UINT8  SEM_ACTION_FUNCTION_TYPE;
typedef VS_UINT8  SEM_EVENT_GROUP_TYPE;
typedef VS_UINT8  SEM_EGTI_TYPE;
typedef VS_UINT8  SEM_RULE_TABLE_INDEX_TYPE;


/*
 * Event Identifier Definitions.
 */
#define SE_RESET 0U
#define eButton1 1U
#define eButton2 2U
#define eButton3 3U


/*
 * Name        : LightingSystemVSDeduct
 *
 * Description : The function deduces all the relevant action expressions on
 *               the basis of the given event, the internal current state
 *               vector and the transitions in the VS System. All the
 *               relevant action expressions are then called and all the
 *               next states are changed.
 *
 * Argument    : EventNo:
 *                 Event number to be processed.
 *
 *               Variable number of arguments:
 *                 Used if at least one event has a parameter.
 *                 The function call must include one argument for each type
 *                 name declared in the parameter list for each event.
 *                 
 *                 This sample declaration is for an event with three
 *                 parameters:
 *                 
 *                   EventName (VS_UINT8 par1, VS_CHAR par2, VS_INT par3)
 *                 
 *                 How to call the LightingSystemVSDeduct function for the
 *                 event EventName:
 *                 
 *                   LightingSystemVSDeduct(EventName, par1, par2, par3);
 *
 * Return      : Completion code:
 *
 *                 SES_CONTRADICTION:
 *                   Contradiction detected, the VS System is not
 *                   consistent. Check the VS System.
 *                   You will also get this error code here if you forget to
 *                   call the LightingSystemVSInitAll function.
 *
 *                 SES_SIGNAL_QUEUE_FULL:
 *                   The signal queue is full. Increase the signal queue
 *                   size in the VS System.
 *
 *                 SES_FOUND:
 *                   Success. The internal state vector was updated.
 *
 *                 SES_RANGE_ERR:
 *                   The event given to this function is out of range.
 *
 *                 SES_OKAY:
 *                   Success.
 *
 * Portability : ANSI-C Compiler.
 */
VSResult LightingSystemVSDeduct (SEM_EVENT_TYPE EventNo);


/*
 * Name        : LightingSystemVSElementName
 *
 * Description : The function gets a pointer to the explanation of the
 *               specified identifier.
 *
 * Argument    : IdentType:
 *                 Must contain the identifier type of the identifier
 *                 number. It can be EVENT_TYPE or STATE_TYPE.
 *
 *               IdentNo:
 *                 Must contain the index number of an identifier.
 *
 *               Text:
 *                 Must be an address of a pointer to a text string. If the
 *                 function terminates successfully, the text pointer
 *                 contains the address of the explanation of the specified
 *                 identifier.
 *
 * Return      : Completion code:
 *
 *                 SES_RANGE_ERR:
 *                   Identifier number is out of range.
 *
 *                 SES_TYPE_ERR:
 *                   The identifier type is not correct. Remember to include
 *                   the wanted text in the VS System and specify the
 *                   correct identifier type when calling this function.
 *
 *                 SES_OKAY:
 *                   Success.
 *
 * Portability : ANSI-C Compiler.
 */
VSResult LightingSystemVSElementExpl (IdentifierType IdentType, SEM_EXPLANATION_TYPE IdentNo, char const * * Text);


/*
 * Name        : LightingSystemVSElementName
 *
 * Description : The function gets a pointer to the ASCII name of the
 *               specified identifier.
 *
 * Argument    : IdentType:
 *                 Must contain the identifier type of the identifier
 *                 number. It can be EVENT_TYPE or STATE_TYPE.
 *
 *               IdentNo:
 *                 Must contain the index number of an identifier.
 *
 *               Text:
 *                 Must be an address of a pointer to a text string. If the
 *                 function terminates successfully, the text pointer
 *                 contains the address of the name of the specified
 *                 identifier.
 *
 * Return      : Completion code:
 *
 *                 SES_RANGE_ERR:
 *                   Identifier number is out of range.
 *
 *                 SES_TYPE_ERR:
 *                   The identifier type is not correct. Remember to include
 *                   the wanted text in the VS System and specify the
 *                   correct identifier type when calling this function.
 *
 *                 SES_OKAY:
 *                   Success.
 *
 * Portability : ANSI-C Compiler.
 */
VSResult LightingSystemVSElementName (IdentifierType IdentType, SEM_EXPLANATION_TYPE IdentNo, char const * * Text);


/*
 * Name        : LightingSystemVSInitAll
 *
 * Description : The function is a wrapper to all initialization 
 *               functions. The function calls the following functions
 *               in the listed order (provided the specific function 
 *               exists): 
 *                 LightingSystemVSInitExternalVariables
 *                 LightingSystemVSInitInternalVariables
 *
 * Argument    : None.
 */
void LightingSystemVSInitAll (void);


/*
 * Name        : LightingSystemVSMachine
 *
 * Description : The function will return the state machine index of the
 *               specified state.
 *
 * Argument    : StateNo:
 *                 State index number.
 *
 *               StateMachineNo:
 *                 Pointer to store the found state machine index number of
 *                 the specified state.
 *
 * Return      : Completion code:
 *
 *                 SES_RANGE_ERR:
 *                   State index is out of range.
 *
 *                 SES_FOUND:
 *                   Success. State machine index number found.
 *
 * Portability : ANSI-C Compiler.
 */
VSResult LightingSystemVSMachine (SEM_STATE_TYPE StateNo, SEM_STATE_MACHINE_TYPE *StateMachineNo);


/*
 * Name        : LightingSystemVSState
 *
 * Description : The function will return the current state of the specified
 *               state machine.
 *               The function must be enabled by its VS Coder option.
 *
 * Argument    : StateMachineNo:
 *                 State machine number.
 *
 *               StateNo:
 *                 Pointer to store the current state of the specified state
 *                 machine.
 *
 * Return      : Completion code:
 *
 *                 SES_RANGE_ERR:
 *                   State machine index is out of range.
 *
 *                 SES_FOUND:
 *                   Success. State number index found.
 *
 * Portability : ANSI-C Compiler.
 */
VSResult LightingSystemVSState (SEM_STATE_MACHINE_TYPE StateMachineNo, SEM_STATE_TYPE *StateNo);


/*
 * Action Function Prototypes
 */
extern void Blue_LED_ON (void);
extern void LEDs_OFF (void);
extern void Red_LED_ON (void);


#endif /* ifndef visualSTATE_LIGHTINGSYSTEM_H */
