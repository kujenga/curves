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

class Window
{
    
public:
    // bool return value indicates whether or not the event should continue to be passed down along the view stack
    virtual bool draw()=0;
    // handling of glut events. default to returning false, indicating the window did not absorb the event
    bool respondToMouseEvent(int button, int state, float2 point);
    bool respondToMoveEvent(float2 point);
    bool respondToKeyboardEvent(unsigned char c);
};

#endif /* defined(__curves__Window__) */
