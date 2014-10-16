//
//  catmullclark.h
//  curves
//
//  Created by Aaron Taylor on 10/12/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__catmullclark__
#define __curves__catmullclark__

#include <stdio.h>

#include "freeform.h"
#include "polyline.h"

#define MESH_STEPS 4

class CatmullClark : public Freeform {
protected:
    // holds the subdivided mesh points and handles all value calculation based on those
    Polyline *holder = new Polyline();
public:
    void recomputeHolder(int depth);
    
    // calls superclass constructor
    CatmullClark(void) : Freeform() {}
    CatmullClark(const Freeform& previous) : Freeform(previous) {}
    
    void addControlPoint(float2 p);
    
    void moveControlPoint(int i, float2 pos);
    
    float2 getPoint(float t);
    float2 getDerivative(float t);
};

#endif /* defined(__curves__catmullclark__) */
