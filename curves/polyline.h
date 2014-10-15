//
//  polyline.h
//  curves
//
//  Created by Aaron Taylor on 10/15/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__polyline__
#define __curves__polyline__

#include <stdio.h>

#include "freeform.h"

class Polyline : public Freeform {
public:
    // calls superclass constructor
    Polyline(void) : Freeform() {}
    Polyline(const Freeform& previous) : Freeform(previous) {}
    
    void addControlPoint(float2 p);
    
    float2 getPoint(float t);
    float2 getDerivative(float t);
};

#endif /* defined(__curves__polyline__) */
