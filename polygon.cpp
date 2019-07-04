#include "polygon.h"

Polygon::Polygon()
{

}

Polygon::Polygon(std::vector<Line> lines) {
    this->lines = lines;
    this->nrOfPoints = lines.size()*2;

    for (auto line : lines) {
        this->V.push_back(Point(line.start.x, line.start.y));
    }
    this->V.push_back(Point(lines[0].start.x, lines[0].start.y));

    this->simple_Polygon(*this);

}

bool Polygon::isSimple() {
    for (std::size_t idx=0; idx<lines.size(); ++idx) {
        for (std::size_t idx2=0; idx2<lines.size(); ++idx2) {
            if (idx!=idx2 && idx!=idx2-1 && idx!=idx2+1) {
                if (lines[idx].isIntersecting(lines[idx2])) return false;
            }
        }
    }
    return true;
}

bool Polygon::simple_Polygon(Polygon Pn)
{
    EventQueue  Eq(Pn);
    SweepLine   SL(Pn);
    Event*      e;                  // the current event
    SweepLineSegment*      s;                  // the current SL segment

    // This loop processes all events in the sorted queue
    // Events are only left or right vertices since
    // No new events will be added (an intersect => Done)
    while (e = Eq.next()) {         // while there are events
        if (e->type == EventType::Left) {      // process a left vertex
            s = SL.add(e);          // add it to the sweep line
            if (SL.intersect(  s, s->above))
                return false;      // Pn is NOT simple
            if (SL.intersect(  s, s->below))
                return false;      // Pn is NOT simple
        }
        else {                      // processs a right vertex
            s = SL.find(e);
            if (SL.intersect(  s->above, s->below))
                return false;      // Pn is NOT simple
            SL.remove(s);           // remove it from the sweep line
        }
    }
    return true;      // Pn IS simple
}

