#pragma once
#include <cstdlib>

#include "point.h"

// Copyright 2001 softSurfer, 2012 Dan Sunday
// This code may be freely used and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from its use.
// Users of this code must verify correctness for their application.


// Assume that classes are already given for the objects:
//    Point with 2D coordinates {float x, y;}
//    Polygon with n vertices {int n; Point *V;} with V[n]=V[0]
//    Tnode is a node element structure for a BBT
//    BBT is a class for a Balanced Binary Tree
//        such as an AVL, a 2-3, or a  red-black tree
//        with methods given by the  placeholder code:

typedef struct _BBTnode Tnode;
struct _BBTnode {
    void* val;
    // plus node mgmt info ...
};

class BBT {
    Tnode   *root;
public:
    BBT() {root = nullptr;}   // constructor
    ~BBT() {freetree();}        // destructor

    Tnode*  insert( void* ){};       // insert data into the tree
    Tnode*  find( void* ){};         // find data from the tree
    Tnode*  next( Tnode* ){};        // get next tree node
    Tnode*  prev( Tnode* ){};        // get previous tree node
    void    remove( Tnode*  ){};     // remove node from the tree
    void    freetree(){};            // free all tree data structs
};
// NOTE:
// Code for these methods must be provided for the algorithm to work.
// We have not provided it since binary tree algorithms are well-known
// and code is widely available. Further, we want to reduce the clutter
// accompanying the essential sweep line algorithm.
//===================================================================




extern void
qsort(void*, unsigned, unsigned, int(*)(const void*,const void*));


void quickSort(int arr[], int left, int right);



// xyorder(): determines the xy lexicographical order of two points
//      returns: (+1) if p1 > p2; (-1) if p1 < p2; and  0 if equal
int xyorder( Point* p1, Point* p2 );

// isLeft(): tests if point P2 is Left|On|Right of the line P0 to P1.
//      returns: >0 for left, 0 for on, and <0 for  right of the line.
//      (see Algorithm 1 on Area of Triangles)
inline float
isLeft( Point P0, Point P1, Point P2 )
{
    return (P1.x - P0.x)*(P2.y - P0.y) - (P2.x - P0.x)*(P1.y -  P0.y);
}
//===================================================================
