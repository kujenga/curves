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
#include "StateManager.h"

class Window
{
protected:
    
    StateManager *applicationStateManager;
    
    float2 transformedFloat2(float x, float y)
    {
        return scale * float2(x, y) + origin;
    }
    bool pointWithinBounds(float2 point)
    {
        bool horizontal = origin.x - scale.x < point.x && origin.x + scale.x > point.x;
        bool vertical = origin.y - scale.y < point.y && origin.y + scale.y > point.y;
        return horizontal && vertical;
    }
public:
    void setApplicationStateManager(StateManager *appStateManager) { applicationStateManager = appStateManager; }
    
    // used to modify position and shape of the window if they are used by the subclass implementation
    float2 origin = float2();
    float2 scale = float2(1.0, 1.0);
    
    // bool return value indicates whether or not the event should continue to be passed down along the view stack
    virtual bool draw()=0;
    
    // handling of glut events. default to returning false, indicating the window did not absorb the event
    virtual bool respondToMouseEvent(int button, int state, float2 point);
    virtual bool respondToMoveEvent(float2 point);
    virtual bool respondToKeyboardEvent(unsigned char c);
};

#endif /* defined(__curves__Window__) */
