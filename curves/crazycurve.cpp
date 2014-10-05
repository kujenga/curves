//
//  CrazyCurve.cpp
//  curves
//
//  Created by Aaron Taylor on 9/25/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "CrazyCurve.h"

#define SCALE 0.05

float2 CrazyCurve::getPoint(float t)
{
    t = 2*M_PI*t;
    float x = 16.0*sinf(t)*sinf(t)*sinf(t);
    float y = 13.0*cosf(t)-5*cosf(2*t)-2*cosf(3*t)-cosf(4*t);
    return float2(x*SCALE, y*SCALE);
}

float2 CrazyCurve::getDerivative(float t)
{
    t = 2*M_PI*t;
    float dx = 48*powf(sinf(t),2.0)*cosf(t);
    float dy = -13.0*sinf(t)+10*sinf(2*t)+6*sinf(3*t)+4*sinf(4*t);
    return float2(dx,dy);
}