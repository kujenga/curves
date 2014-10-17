//
//  hermiteinterp.h
//  curves
//
//  Created by Aaron Taylor on 10/12/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__hermiteinterp__
#define __curves__hermiteinterp__

#include <stdio.h>

#include "freeform.h"

class HermiteInterp : public Freeform {
protected:
    void drawControlPointTangents();
public:
    // calls superclass constructor
    HermiteInterp(void) : Freeform() {}
    HermiteInterp(const Freeform& previous) : Freeform(previous) {}
    
    void addControlPoint(float2 p);
    void drawControlPoints();
    
    int currentControlPoint(float2 test);
    void moveControlPoint(int i, float2 pos);
    
    float2 getPoint(float t);
    float2 getDerivative(float t);
};

#endif /* defined(__curves__hermiteinterp__) */
