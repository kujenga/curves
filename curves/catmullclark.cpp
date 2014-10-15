//
//  catmullclark.cpp
//  curves
//
//  Created by Aaron Taylor on 10/12/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "catmullclark.h"

void CatmullClark::recomputeHolder(int depth)
{
    if (depth == 0) {
        return;
    }
    Polyline tmpHolder = Polyline();
    float2 fst = holder.controlPointVectorElement(0);
    float2 snd = holder.controlPointVectorElement(1);
    tmpHolder.addControlPoint(fst);
    tmpHolder.addControlPoint(fst+(snd-fst)*0.5);
    for (int p = 1; p < holder.controlPointVectorSize()-1; p++) {
        float2 prev = holder.controlPointVectorElement(p-1);
        float2 cur = holder.controlPointVectorElement(p);
        float2 next = holder.controlPointVectorElement(p+1);
        
        float2 edge1 = prev + (cur-prev)*0.5;
        float2 edge2 = cur + (next-cur)*0.5;
        
        float2 newCur = (edge1 + cur + edge2)*0.333333;
        
        tmpHolder.addControlPoint(newCur);
        tmpHolder.addControlPoint(edge2);
    }
    tmpHolder.addControlPoint(controlPoints.back());
    holder = tmpHolder;
    recomputeHolder(depth-1);
}

void CatmullClark::addControlPoint(float2 newPoint)
{
    controlPoints.push_back(newPoint);
    
    // reset holder to have just the new control points
    const CatmullClark tmpThis = *this;
    holder = Polyline(tmpThis);
    
    if (controlPointVectorSize() > 2) {
        // recompute the holder recursively
        recomputeHolder(MESH_STEPS);
    }
}

void CatmullClark::moveControlPoint(int i, float2 pos)
{
    Freeform::moveControlPoint(i, pos);
//    recomputeHolder(MESH_STEPS);
}

float2 CatmullClark::getPoint(float t)
{
    if (holder.controlPointVectorSize() == 0) {
        return float2();
    }
    return holder.getPoint(t);
}

float2 CatmullClark::getDerivative(float t)
{
    if (holder.controlPointVectorSize() == 0) {
        return float2();
    }
    return holder.getDerivative(t);
}
