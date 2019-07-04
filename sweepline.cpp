#include "sweepline.h"
#include "slseg.h"

SweepLine::SweepLine(Polygon P)            // constructor
{ nv = P.nrOfPoints; Pn = &P; }

SweepLine::~SweepLine()                 // destructor
{ Tree.freetree();}

SweepLineSegment* SweepLine::add( Event* E )
{
    // fill in SLseg element data
    SweepLineSegment* s = new SweepLineSegment();
    s->edge  = E->edgeIdx;

    // if it is being added, then it must be a LEFT edge event
    // but need to determine which endpoint is the left one
    Point* v1 = &(Pn->V[s->edge]);
    Point* v2 = &(Pn->V[s->edge+1]);
    if (xyorder( v1, v2) < 0) { // determine which is leftmost
        s->lP = *v1;
        s->rP = *v2;
    }
    else {
        s->rP = *v1;
        s->lP = *v2;
    }
    s->above = nullptr;
    s->below = nullptr;

    // add a node to the balanced binary tree
    Tnode* nd = Tree.insert(s);
    Tnode* nx = Tree.next(nd);
    Tnode* np = Tree.prev(nd);
    if (nx != nullptr) {
        s->above = (SweepLineSegment*)nx->val;
        s->above->below = s;
    }
    if (np != nullptr) {
        s->below = (SweepLineSegment*)np->val;
        s->below->above = s;
    }
    return s;
}

SweepLineSegment* SweepLine::find( Event* E )
{
    // need a segment to find it in the tree
    SweepLineSegment* s = new SweepLineSegment;
    s->edge  = E->edgeIdx;
    s->above = nullptr;
    s->below = nullptr;

    Tnode* nd = Tree.find(s);
    delete s;
    if (nd == nullptr)
        return nullptr;

    return (SweepLineSegment*)nd->val;
}

void SweepLine::remove( SweepLineSegment* s )
{
    // remove the node from the balanced binary tree
    Tnode* nd = Tree.find(s);
    if (nd == nullptr)
        return;       // not there

    // get the above and below segments pointing to each other
    Tnode* nx = Tree.next(nd);
    if (nx != nullptr) {
        SweepLineSegment* sx = (SweepLineSegment*)(nx->val);
        sx->below = s->below;
    }
    Tnode* np = Tree.prev(nd);
    if (np != nullptr) {
        SweepLineSegment* sp = (SweepLineSegment*)(np->val);
        sp->above = s->above;
    }
    Tree.remove(nd);       // now  can safely remove it
    delete s;
}

// test intersect of 2 segments and return: 0=none, 1=intersect
bool SweepLine::intersect( SweepLineSegment* s1, SweepLineSegment* s2)
{
    if (s1 == nullptr || s2 == nullptr)
        return false;       // no intersect if either segment doesn't exist

    // check for consecutive edges in polygon
    int e1 = s1->edge;
    int e2 = s2->edge;
    if (((e1+1)%nv == e2) || (e1 == (e2+1)%nv))
        return false;       // no non-simple intersect since consecutive

    // test for existence of an intersect point
    float lsign, rsign;
    lsign = isLeft(s1->lP, s1->rP, s2->lP);    //  s2 left point sign
    rsign = isLeft(s1->lP, s1->rP, s2->rP);    //  s2 right point sign
    if (lsign * rsign > 0) // s2 endpoints have same sign  relative to s1
        return false;       // => on same side => no intersect is possible
    lsign = isLeft(s2->lP, s2->rP, s1->lP);    //  s1 left point sign
    rsign = isLeft(s2->lP, s2->rP, s1->rP);    //  s1 right point sign
    if (lsign * rsign > 0) // s1 endpoints have same sign  relative to s2
        return false;       // => on same side => no intersect is possible
    // the segments s1 and s2 straddle each other
    return true;            // => an intersect exists
}
//===================================================================
