#pragma once
#include "point.h"
#include "polygon.h"
#include "bbt.h"
#include "event.h"
#include "slseg.h"

class Polygon;

// SweepLine Class



// the Sweep Line itself
class SweepLine {
    int      nv;            // number of vertices in polygon
    Polygon* Pn;            // initial Polygon
    BBT      Tree;          // balanced binary tree
public:
    SweepLine(Polygon P);
    ~SweepLine(void);

    SweepLineSegment*   add( Event* );
    SweepLineSegment*   find( Event* );
    bool      intersect( SweepLineSegment*, SweepLineSegment*  );
    void     remove( SweepLineSegment* );
};
