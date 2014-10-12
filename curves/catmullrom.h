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

#include "freeform.h"

class CatmullRom : public Freeform {
protected:
    
public:
    // calls superclass constructor
    CatmullRom(void) : Freeform() {}
    CatmullRom(const Freeform& previous);
    
    void addControlPoint(float2 p);
    
    float2 getPoint(float t);
    float2 getDerivative(float t);
};

#endif /* defined(__curves__catmullrom__) */
