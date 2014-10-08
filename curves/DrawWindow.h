//
//  DrawWindow.h
//  curves
//
//  Created by Aaron Taylor on 10/6/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__DrawWindow__
#define __curves__DrawWindow__

#include <stdio.h>
#include <vector>

#include "Window.h"


class DrawWindow : public Window {
    // all the curves contained by the current window
    std::vector<Curve*> curves;
    
    // index of the currently active curve
    int activeCurveIndex;
    // index of the currently active point along the curve
    int activePointIndex;
    // whether or not a point along the active curve is currently being dragged
    bool isDragging;
public:
    // draws the contents of the window
    bool draw();
    
    // all functions inherited from window, need to specify non-virtual and implement
    bool respondToMouseEvent(int button, int state, float2 point);
    bool respondToMoveEvent(float2 point);
//    bool respondToKeyboardEvent(unsigned char c);
    bool respondToDisplayEvent();
};

#endif /* defined(__curves__DrawWindow__) */
