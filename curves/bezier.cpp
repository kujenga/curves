//
//  freeform.cpp
//  curves
//
//  Created by Aaron Taylor on 9/25/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "bezier.h"

void Bezier::addControlPoint(float2 p)
{
    controlPoints.push_back(p);
}

static double bernstein(int i, int n, double t) {
    if(n == 1) {
        if(i == 0) return 1-t;
        if(i == 1) return t;
        return 0;
    }
    if(i < 0 || i > n) return 0;
    return (1-t)*bernstein(i, n-1, t) + t*bernstein(i-1, n-1, t);
}

float2 Bezier::getPoint(float t)
{
    float2 r(0.0, 0.0);
    // for every control point
    // compute weight using the Bernstein formula
    // add control point to r, weighted
    int siz = (int)controlPoints.size();
    for (int i = 0; i < siz; i++) {
        float2 ri = controlPoints.at(i);
        ri *= bernstein(i, siz-1, t);
        r += ri;
    }
    return r;
}

static double bernsteinDerivative(int i, int n, double t) {
    if(n == 1) {
        if(i == 0) return -1;
        if(i == 1) return 1;
        return 0;
    }
    if(i < 0 || i > n) return 0;
    return -1*bernstein(i, n-1, t) + (1-t)*bernsteinDerivative(i, n-1, t) +
           bernstein(i-1, n-1, t) + t*bernsteinDerivative(i-1, n-1, t);
}

float2 Bezier::getDerivative(float t)
{
    float2 r(0.0, 0.0);
    // for every control point
    // compute weight using the Bernstein formula
    // add control point to r, weighted
    int siz = (int)controlPoints.size();
    for (int i = 0; i < siz; i++) {
        float2 ri = controlPoints.at(i);
        ri *= bernsteinDerivative(i, siz-1, t);
        r += ri;
    }
    return r;
}