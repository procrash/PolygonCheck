#pragma once
#include "point.h"

#include "bbt.h"
#include "polygon.h"
#include "event.h"


class Polygon;

// EventQueue Class


int E_compare( const void* v1, const void* v2 );

// the EventQueue is a presorted array (no insertions needed)
class EventQueue {
    unsigned long      nrOfEvents;                // total number of events in array
    int      idxNextEventOnQueue;                // index of next event on queue
    Event*   Edata;             // array of all events
    Event**  eventQueue;                // sorted list of event pointers
public:
    EventQueue(Polygon P);     // constructor
    ~EventQueue(void)           // destructor
    { delete eventQueue; delete Edata;}

    Event*   next();                     // next event on queue
};

