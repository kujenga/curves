//
//  CrazyCurve.h
//  curves
//
//  Created by Aaron Taylor on 9/25/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__crazycurve__
#define __curves__crazycurve__

#include <stdio.h>

#include "curve.h"


class CrazyCurve : public Curve {
    
public:
    float2 getPoint(float t);
    float2 getDerivative(float t);
};

#endif /* defined(__curves__circle__) */
