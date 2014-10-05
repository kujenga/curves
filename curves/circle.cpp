//
//  circle.cpp
//  curves
//
//  Created by Aaron Taylor on 9/18/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include <math.h>

#include "circle.h"

void Circle::setValues(float x, float y, float r) {
    xVal = x;
    yVal = y;
    radius = r;
}

float2 Circle::getPoint(float t)
{
    float xCur = radius*sinf(2*M_PI*t)+xVal;
    float yCur = radius*cosf(2*M_PI*t)+yVal;
    return float2(xCur, yCur);
}

float2 Circle::getDerivative(float t)
{
    float dx = 2*M_PI*radius*cosf(2*M_PI*t);
    float dy = -2*M_PI*radius*sinf(2*M_PI*t);
    return float2(dx,dy);
}