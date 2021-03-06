
#include <stdio.h>
#include "..\coderGenerated\coder_adaptive\Lighting.h"
#include "eventQueue\simpleEventHandler.h"


void DisplayEventNames();
void DisplayStateNames();
void readAndAdd(VS_BOOL *end);
void error(VS_BOOL *end);

int main()
{
	/*If the event queue is full (UCC_QUEUE_FULL) or not (UCC_OK)*/	
	VS_UINT8 cc;
	SEM_EVENT_TYPE eventNo = SE_RESET;
	VS_BOOL finish = 0;

	/*Initialize the VS System*/
	LightingSystemVSInitAll();

	SEQ_Initialize();

	if ((cc = SEQ_AddEvent(SE_RESET)) != UCC_OK){
		error(&finish);
	}

	DisplayEventNames(); /* Display available event names */

	printf("  Type in an event number and press return.\n");

	/* Do forever */
	while (finish != 1){
		/* Get next event from queue */
		if (SEQ_RetrieveEvent(&eventNo) != UCC_QUEUE_EMPTY){
			/* Deduct the event. */
			if ((cc = LightingSystemVSDeduct(eventNo)) != SES_OKAY){
				error(&finish);
			}
			/* Print current state configuration after processing the event */
			DisplayStateNames();
		}

		/*Read event from keyboard and add it to the queue*/
		readAndAdd(&finish);
	}

    return 0;
}


void DisplayEventNames(){

	SEM_EVENT_TYPE i;
	for (i = 0u; i < VS_NOF_EVENTS; i++)
	{
		VS_UINT8 e1 = 0u; 
		char const * event_name_p;
		/* Print event name and explanation. */
		e1 = LightingSystemVSElementName(EVENT_TYPE, i, &event_name_p);       
		if (e1 == 0u){
			printf("\n%s \t=%i", event_name_p, i);
		}
		else{
			/* If you end up here it is probably due to disabled coder options for
			event name inclusion, state name inclusion and/or event explanation
			inclusion.  (See the "Names" tab in visualSTATE coder options.) */
			break;
		}
	}
	printf("\n\n");
}

void DisplayStateNames(){

	SEM_STATE_TYPE StateNo = STATE_UNDEFINED;
	SEM_STATE_MACHINE_TYPE i;

	for (i = 0u; i < VS_NOF_STATE_MACHINES; i++){
		if (LightingSystemVSState(i, &StateNo) != SES_FOUND){
			printf("\nState machine %d is in an undefined state", i);
		}
		else{
			char const * state_name_p;
			VS_UINT8 e = 0u;
			/* Print state machine number and state number. */
			e = LightingSystemVSElementName(STATE_TYPE, StateNo, &state_name_p);
			if (e == 0u){
				printf("\nState machine %d: state %s", i, state_name_p);
			}
			else{
				break;
			}
		}
	}
	printf("\nEnter %i to exit\n", EVENT_UNDEFINED);
}

void readAndAdd(VS_BOOL *end){
	VS_UINT8 cc;
	VS_INT scan_event;
	SEM_EVENT_TYPE event;

	printf("event:");
	scanf("%i", &scan_event);

	event = (SEM_EVENT_TYPE)scan_event;
	if (event != EVENT_UNDEFINED){
		if ((cc = SEQ_AddEvent(event)) != UCC_OK){
			error(end);
		}
	}
	else{
		error(end);
	}
}

void error(VS_BOOL *end) {
	printf("\nERROOOR!");
	*end = (VS_BOOL)1;
}