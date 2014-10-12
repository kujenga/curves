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

class CubicHermiteInterp : public Freeform {
protected:
    
public:
    // calls superclass constructor
    CubicHermiteInterp(void) : Freeform() {}
    CubicHermiteInterp(const Freeform& previous);
    
    void addControlPoint(float2 p);
    
    float2 getPoint(float t);
    float2 getDerivative(float t);
};

#endif /* defined(__curves__hermiteinterp__) */
