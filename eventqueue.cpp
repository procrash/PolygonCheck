#include "eventqueue.h"


// EventQueue Routines
EventQueue::EventQueue( Polygon P )
{
    idxNextEventOnQueue = 0;
    nrOfEvents = 2*P.nrOfPoints;

    Edata = static_cast<Event*>(new Event[nrOfEvents]);
    // Eq = (Event**)(new (Event*))[nrOfEvents];
    eventQueue = static_cast<Event**>((new Event*[nrOfEvents]));
    for (int i=0; i < nrOfEvents; i++)           // init Eq array pointers
        eventQueue[i] = &Edata[i];

    // Initialize event queue with edge segment endpoints
    for (int i=0; i < P.nrOfPoints; i++) {        // init data for edge i
        eventQueue[2*i]->edgeIdx = i;
        eventQueue[2*i+1]->edgeIdx = i;
        eventQueue[2*i]->eventVertex   = &(P.V[i]);
        eventQueue[2*i+1]->eventVertex = &(P.V[i+1]);
        if (xyorder( &P.V[i], &P.V[i+1]) < 0)  { // determine type
            eventQueue[2*i]->type    = EventType::Left;
            eventQueue[2*i+1]->type = EventType::Right;
        }
        else {
            eventQueue[2*i]->type    = EventType::Right;
            eventQueue[2*i+1]->type = EventType::Left;
        }
    }
    // Sort Eq[] by increasing x and y
    qsort( eventQueue, nrOfEvents, sizeof(Event*), E_compare );
}

Event* EventQueue::next()
{
    if (idxNextEventOnQueue >= nrOfEvents)
        return nullptr;
    else
        return eventQueue[idxNextEventOnQueue++];
}
//===================================================================

int E_compare(const void *v1, const void *v2) // qsort compare two events
{
    Event**    pe1 = (Event**)(v1);
    Event**    pe2 = (Event**)(v2);

    return xyorder( (*pe1)->eventVertex, (*pe2)->eventVertex );
}
