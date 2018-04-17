/*
 * Id:        LightingSystem.c
 *
 * Function:  Contains all API functions.
 *
 * This is an automatically generated file. It will be overwritten by the Coder.
 * 
 * DO NOT EDIT THE FILE!
 */


#include "LightingSystem.h"


/*
 * State Identifier Definitions.
 */
#define MY_Topstate_Region1_Select_LED 0U
#define MY_Topstate_Region1_Red_LED 1U
#define MY_Topstate_Region1_Blue_LED 2U


/*
 * State Machine Identifier Definitions.
 */
#define M_MY_Topstate_Region1 0U


static SEM_STATE_TYPE LightingSystemCSV[1U];


static const SEM_STATE_MACHINE_TYPE SMI[] =
{
  0U,
  0U,
  0U
};


VSResult LightingSystemVSDeduct (SEM_EVENT_TYPE EventNo)
{

  /* scoped for events */
  {
    SEM_STATE_TYPE WSV[1U] =
    {
      STATE_UNDEFINED
    };

    switch (EventNo)
    {
    case SE_RESET:
      {
        WSV[M_MY_Topstate_Region1/*0*/] = MY_Topstate_Region1_Select_LED;
      }
      break;

    case eButton1:
      {
        if (LightingSystemCSV[M_MY_Topstate_Region1/*0*/] == MY_Topstate_Region1_Select_LED)
        {
          Red_LED_ON();
          WSV[M_MY_Topstate_Region1/*0*/] = MY_Topstate_Region1_Red_LED;
        }
        else if (LightingSystemCSV[M_MY_Topstate_Region1/*0*/] == MY_Topstate_Region1_Blue_LED)
        {
          Red_LED_ON();
          WSV[M_MY_Topstate_Region1/*0*/] = MY_Topstate_Region1_Red_LED;
        }
      }
      break;

    case eButton2:
      {
        if (LightingSystemCSV[M_MY_Topstate_Region1/*0*/] == MY_Topstate_Region1_Red_LED)
        {
          Blue_LED_ON();
          WSV[M_MY_Topstate_Region1/*0*/] = MY_Topstate_Region1_Blue_LED;
        }
      }
      break;

    case eButton3:
      {
        if (LightingSystemCSV[M_MY_Topstate_Region1/*0*/] == MY_Topstate_Region1_Blue_LED)
        {
          LEDs_OFF();
          WSV[M_MY_Topstate_Region1/*0*/] = MY_Topstate_Region1_Select_LED;
        }
      }
      break;

    default:
      return SES_RANGE_ERR;
    }

    /* Change the state vector */
    {
      VS_UINT i;
      for (i = 0U; i < 1U; ++i)
      {
        if (WSV[i] != STATE_UNDEFINED)
        {
          LightingSystemCSV[i] = WSV[i];
        }
      }
    }
  }

  return SES_OKAY;
}


VSResult LightingSystemVSElementExpl (IdentifierType IdentType, SEM_EXPLANATION_TYPE IdentNo, char const * * Text)
{
  VSResult ret = SES_OKAY;
  switch (IdentType)
  {
  case EVENT_TYPE:
    if (IdentNo >= 4U)
    {
      ret = SES_RANGE_ERR;
    }
    else
    {
      static const char* LightingSystemEventExpls[] =
      {
        "",
        "",
        "",
        ""
      };
      *Text = LightingSystemEventExpls[IdentNo];
    }
    break;

  default:
    ret = SES_TYPE_ERR;
    break;
  }
  return ret;
}


VSResult LightingSystemVSElementName (IdentifierType IdentType, SEM_EXPLANATION_TYPE IdentNo, char const * * Text)
{
  VSResult ret = SES_OKAY;
  switch (IdentType)
  {
  case EVENT_TYPE:
    if (IdentNo >= 4U)
    {
      ret = SES_RANGE_ERR;
    }
    else
    {
      static const char* LightingSystemEventNames[] =
      {
        "SE_RESET",
        "eButton1",
        "eButton2",
        "eButton3"
      };
      *Text = LightingSystemEventNames[IdentNo];
    }
    break;

  case STATE_TYPE:
    if (IdentNo >= 3U)
    {
      ret = SES_RANGE_ERR;
    }
    else
    {
      static const char* LightingSystemStateNames[] =
      {
        "MY_Topstate.Region1.Select_LED",
        "MY_Topstate.Region1.Red_LED",
        "MY_Topstate.Region1.Blue_LED"
      };
      *Text = LightingSystemStateNames[IdentNo];
    }
    break;

  default:
    ret = SES_TYPE_ERR;
    break;
  }
  return ret;
}


void LightingSystemVSInitAll (void)
{
  SEM_STATE_MACHINE_TYPE i;
  for (i = 0U; i < 1U; ++i)
  {
    LightingSystemCSV[i] = STATE_UNDEFINED;
  }
}


VSResult LightingSystemVSMachine (SEM_STATE_TYPE StateNo,
  SEM_STATE_MACHINE_TYPE *StateMachineNo)
{
  if (StateNo >= 3U)
  {
    return SES_RANGE_ERR;
  }
  *StateMachineNo = SMI[StateNo];
  return SES_FOUND;
}


VSResult LightingSystemVSState (SEM_STATE_MACHINE_TYPE StateMachineNo, SEM_STATE_TYPE *StateNo)
{
  if (StateMachineNo >= 1U)
  {
    return SES_RANGE_ERR;
  }
  *StateNo = LightingSystemCSV[StateMachineNo];
  return SES_FOUND;
}
