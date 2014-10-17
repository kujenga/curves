//
//  freeform.h
//  curves
//
//  Created by Aaron Taylor on 10/1/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__freeform__
#define __curves__freeform__

#include <stdio.h>
#include <vector>

#include "curve.h"

class Freeform : public Curve {
protected:
    std::vector<float2> controlPoints;
    
    void drawSingleControlPoint(int index);
public:
    // constructors
    Freeform(void);
    Freeform(const Freeform& previous);
    // point manipulation
    virtual float2 getPoint(float t)=0;
    virtual void addControlPoint(float2 p)
    {
        controlPoints.push_back(p);
    }
    virtual void deleteControlPoint(int indx)
    {
        printf("%lu\n",controlPoints.size());
        controlPoints.erase(controlPoints.begin() + indx);
        printf("%lu\n",controlPoints.size());
    }
    // returns hidden index of point, or -1 if not found
    virtual int currentControlPoint(float2 test);
    virtual void moveControlPoint(int i, float2 pos);
    virtual void drawControlPoints();
    bool pointMatch(float2 p1, float2 p2);
    
    // const getter methods for the vector
    const int controlPointVectorSize() { return (int)controlPoints.size(); }
    const float2 controlPointVectorElement(int i) { return controlPoints.at(i); }
};

#endif /* defined(__curves__freeform__) */
