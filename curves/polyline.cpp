//
//  polyline.cpp
//  curves
//
//  Created by Aaron Taylor on 10/15/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "polyline.h"

void Polyline::addControlPoint(float2 p)
{
    controlPoints.push_back(p);
}

void Polyline::insertControlPoint(int pos, float2 point)
{
    controlPoints.insert(controlPoints.begin() + pos, point);
}

float2 Polyline::getPoint(float t)
{
    float numPoints = (float)controlPointVectorSize();
    if ((int)numPoints < 2) {
        return controlPoints.at(0);
    }
    int curPoint = (int)floorf(t * (numPoints-1));
    
    // simple approach with fewer necessary calculations
    //if (curPoint == (int)numPoints) {
    //    curPoint--;
    //}
    //return controlPoints.at(curPoint);
    
    if (curPoint == (int)(numPoints-1)) {
        curPoint--;
    }
    float2 prev = controlPoints.at(curPoint);
    float2 next = controlPoints.at(curPoint+1);
    float2 diff = next-prev;
    
    float interPos = t*(numPoints-1) - (float)curPoint;
    return prev + diff*interPos;
}

float2 Polyline::getDerivative(float t)
{
    float numPoints = (float)controlPointVectorSize();
    if (numPoints < 1.5) {
        return float2();
    }
    int curPoint = (int)floorf(t * (numPoints-1));
    if (curPoint+1 == (int)numPoints) {
        curPoint--;
    }
    float2 prev = controlPoints.at(curPoint);
    float2 next = controlPoints.at(curPoint+1);
    return prev-next;
}