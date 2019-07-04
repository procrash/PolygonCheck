#pragma once
#include "point.h"

class Line
{

public:
    Point start;
    Point end;

    Line(Point start, Point end) : start(start), end(end) {

    }

    bool isIntersecting(const Line& other) {
        return (((other.start.x-start.x)*(end.y-start.y) - (other.start.y-start.y)*(end.x-start.x))
                    * ((other.end.x-start.x)*(end.y-start.y) - (other.end.y-start.y)*(end.x-start.x)) < 0)
            &&
            (((start.x-other.start.x)*(other.end.y-other.start.y) - (start.y-other.start.y)*(other.end.x-other.start.x))
                 * ((end.x-other.start.x)*(other.end.y-other.start.y) - (end.y-other.start.y)*(other.end.x-other.start.x)) < 0);

    }

};

