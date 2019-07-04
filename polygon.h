#pragma once

#include <vector>
#include "line.h"
#include "eventqueue.h"
#include "sweepline.h"
#include "point.h"

class EventQueue;
class SweepLine;
class SweepLineSegment;

class Polygon
{
private:
    std::vector<Line> lines;

public:
    unsigned long nrOfPoints = 0; // Number of Points
    std::vector<Point> V;

    Polygon();;

    Polygon(std::vector<Line> lines);



    bool isSimple();

    // simple_Polygon(): test if a Polygon is simple or not
    //     Input:  Pn = a polygon with n vertices V[]
    //     Return: FALSE(0) = is NOT simple
    //             TRUE(1)  = IS simple

    bool
    simple_Polygon( Polygon Pn );
};

