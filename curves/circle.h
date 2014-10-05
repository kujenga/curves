//
//  circle.h
//  curves
//
//  Created by Aaron Taylor on 9/18/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__circle__
#define __curves__circle__

#include <stdio.h>

#include "curve.h"


class Circle : public Curve {
    float xVal = 0.0f;
    float yVal = 0.0f;
    float radius = 1.0f;
public:
    void setValues(float x, float y, float radius);
    float2 getPoint(float t);
    float2 getDerivative(float t);
};

#endif /* defined(__curves__circle__) */
