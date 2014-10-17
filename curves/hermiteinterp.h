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
    
    virtual void addControlPoint(float2 p);
    virtual void drawControlPoints();
    
    virtual int currentControlPoint(float2 test);
    virtual void moveControlPoint(int i, float2 pos);
    
    virtual float2 getPoint(float t);
    virtual float2 getDerivative(float t);
};

#endif /* defined(__curves__hermiteinterp__) */
