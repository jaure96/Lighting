/*****************************************************************************
* visualSTATE Static Event Handler Source File (sample code)
*
* The file implements an event queue with a static size, specified by the
* value of the macro EVENT_QUEUE_SIZE.
*
* Whenever the queue runs full (by a call to SEQ_AddEvent), the event is ig-
* nored and an error is returned.
*
* A function is provided for initializing the queue, as well as functions for
* adding and retrieving events from the queue. See the associated header file
* for descriptions and use of those functions.
*
* The queue is a static variable in this file. If multiple queues are to be
* used, the static variable must be removed and the queue handling functions
* must be modified to take a parameter identifying a particular queue, for
* example a pointer to a queue.
*
* If you read and write from different threads you need to modify the code.
*****************************************************************************/


/* *** include directives *** */

#include "simpleEventHandler.h"


/* *** macro definitions *** */

/** Event queue size. Defines the size of the event queue. */
#ifndef EVENT_QUEUE_SIZE
#define EVENT_QUEUE_SIZE 20u 
#endif


/* *** type definitions *** */

/** Event queue size type. Defines the type for indexes into the event queue.
    The type must be an unsigned ordinal type, capable of holding values in
    the range [0;EVENT_QUEUE_SIZE[. 
    Note that the typedef values for different sizes is just a suggestion.
    Depending on your target MCU and/or compiler it can be beneficial to change 
    these type suggestions. */
#if (EVENT_QUEUE_SIZE <= 0x0100u)
typedef VS_UINT16 SEQ_SIZE_TYPE;
#elif (EVENT_QUEUE_SIZE <= 0x010000u)
typedef VS_UINT16 SEQ_SIZE_TYPE;
#elif (EVENT_QUEUE_SIZE <= 0x01000000u)
typedef VS_UINT32 SEQ_SIZE_TYPE;
#else
#error Cannot determine type of SEQ_SIZE_TYPE
#endif


/** Event queue type. Defines the internal structure of the event queue. */
struct StaticEventQueue
{
  /** Event queue. The array stores events in the queue. */
  SEM_EVENT_TYPE queue[EVENT_QUEUE_SIZE];

  /** Front index into the queue. The front index specifies the index into the
      array, where the next event will be retrieved from. */
  SEQ_SIZE_TYPE front;

  /** Back index into the queue. The back index specifies the index into the
      array, where the next event will be stored. */
  SEQ_SIZE_TYPE back;

};

#ifndef _cplusplus
typedef struct StaticEventQueue StaticEventQueue;
#endif


/* *** variable definitions *** */

/** The event queue. If more than one event queue is needed (for example when
    a visualSTATE project contains more than one system), the event queue must
    be a parameter for all event queue handling functions instead of being a
    static variable. */
static StaticEventQueue eventQueue;


/* *** function definitions *** */

void SEQ_Initialize (void)
{
  SEQ_Clear();
}


UCC_TYPE SEQ_AddEvent (SEM_EVENT_TYPE event)
{
  VS_UINT8 returnCode = UCC_OK; 
  
  /* Test whether the queue is full. */
  if (eventQueue.front == eventQueue.back + 1u)
  {
    returnCode = UCC_QUEUE_FULL;
  }
  else
  {
    /* Store the event in the queue. */
    eventQueue.queue[eventQueue.back] = event;
  
    /* Increment the back queue index. */
    eventQueue.back = (SEQ_SIZE_TYPE) ((eventQueue.back + 1u) % EVENT_QUEUE_SIZE);
  }
  return returnCode;
}


UCC_TYPE SEQ_RetrieveEvent (SEM_EVENT_TYPE* pEvent)
{
   VS_UINT8 returnCode = UCC_OK; 
    
  /* Test whether the queue is empty. */
  if (eventQueue.front == eventQueue.back)
  {
    returnCode = UCC_QUEUE_EMPTY;
  }
  else
  {
    /* Retrieve event from queue. */
    *pEvent = eventQueue.queue[eventQueue.front];
  
    /* Increment the front queue index. */
    eventQueue.front = (SEQ_SIZE_TYPE) ((eventQueue.front + 1u) % EVENT_QUEUE_SIZE);
  }
  return returnCode;
}


void SEQ_Clear (void)
{
  eventQueue.front = eventQueue.back = 0u;
}


VS_BOOL SEQ_EventPendingP (void)
{
  return (VS_BOOL) (eventQueue.front != eventQueue.back);
}
