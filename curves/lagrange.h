//
//  lagrange.h
//  curves
//
//  Created by Aaron Taylor on 10/1/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__lagrange__
#define __curves__lagrange__

#include <stdio.h>
#include <vector>

#include "freeform.h"

class Lagrange : public Freeform {
protected:
    std::vector<float> knots;
    double lagrange(int n, double t);
public:
    // calls superclass constructor
    Lagrange(void) : Freeform() {}
    Lagrange(const Freeform& previous);
    
    void addControlPoint(float2 p);
    
    float2 getPoint(float t);
    float2 getDerivative(float t);
};

#endif /* defined(__curves__lagrange__) */
