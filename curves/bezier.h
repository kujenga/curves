//
//  freeform.h
//  curves
//
//  Created by Aaron Taylor on 9/25/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__bezier__
#define __curves__bezier__

#include <stdio.h>
#include <vector>

#include "freeform.h"


class Bezier : public Freeform {
public:
    // calls superclass constructor
    Bezier(void) : Freeform() {}
    Bezier(const Freeform& previous) : Freeform(previous) {}
    
    void addControlPoint(float2 p);
    
    float2 getPoint(float t);
    float2 getDerivative(float t);
};

#endif /* defined(__curves__freeform__) */
