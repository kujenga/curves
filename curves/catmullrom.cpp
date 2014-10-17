//
//  catmullrom.cpp
//  curves
//
//  Created by Aaron Taylor on 10/12/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "catmullrom.h"

void CatmullRom::recalculateTangents()
{
    if (controlPointVectorSize() < 6) {
        return;
    }
    // iterate over intermediate points and recompute them
    for (int k = 3; k < controlPointVectorSize()-2; k += 2) {
        
        float2 pkminus = controlPointVectorElement(k - 3);
        float2 pkplus = controlPointVectorElement(k + 2);
        
        float tkplus = (float)(k+2);
        float tkminus = (float)(k-3);
        
        controlPoints.at(k) = (pkplus - pkminus) * (1/(tkplus - tkminus));
    }
}

void CatmullRom::addControlPoint(float2 newPoint)
{
    controlPoints.push_back(newPoint);
    controlPoints.push_back(float2(0.0,0.0));
    recalculateTangents();
}

void CatmullRom::moveControlPoint(int i, float2 pos)
{
    HermiteInterp::moveControlPoint(i, pos);
    recalculateTangents();
}

void CatmullRom::drawControlPoints()
{
    HermiteInterp::drawControlPoints();
    
    // skip the hermite's drawing of control points
//    for (int i = 0; i < controlPointVectorSize(); i += 2) {
//        Freeform::drawSingleControlPoint(i);
//    }
}

int CatmullRom::currentControlPoint(float2 test)
{
    for (int i = 0; i < controlPoints.size(); i+=2) {
        float2 cur = controlPoints.at(i);
        if (pointMatch(cur, test)) {
            return i;
        }
    }
    return -1;
}