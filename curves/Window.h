//
//  Window.h
//  curves
//
//  Created by Aaron Taylor on 10/6/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__Window__
#define __curves__Window__

#include <stdio.h>
//#include <vector>

#include "curve.h"
#include "float2.h"

class Window
{
    
public:
    virtual void draw();
    
    bool respondToMouse(int button, int state, float2 point);
    bool respondToMove(float2 point);
};

#endif /* defined(__curves__Window__) */
