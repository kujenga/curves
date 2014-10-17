//
//  catmullrom.h
//  curves
//
//  Created by Aaron Taylor on 10/12/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__catmullrom__
#define __curves__catmullrom__

#include <stdio.h>

#include "hermiteinterp.h"

class CatmullRom : public HermiteInterp {
protected:
    void recalculateTangents();
public:    
    void addControlPoint(float2 p);
    void moveControlPoint(int i, float2 pos);
    
    void drawControlPoints();
    int currentControlPoint(float2 test);
};

#endif /* defined(__curves__catmullrom__) */
