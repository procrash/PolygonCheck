#pragma once

#include "point.h"

enum class EventType{Left, Right};

// Event element data struct
// typedef struct _event Event;
struct Event {
    int       edgeIdx;          // polygon edge i is V[i] to V[i+1]
    EventType type;          // event type: LEFT or RIGHT vertex
    Point*    eventVertex;            // event vertex
};
