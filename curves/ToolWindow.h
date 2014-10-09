//
//  ToolWindow.h
//  curves
//
//  Created by Aaron Taylor on 10/6/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__ToolWindow__
#define __curves__ToolWindow__

#include <stdio.h>
#include <vector>

#include "Window.h"
#include "ToolView.h"

class ToolWindow : public Window {
    std::vector<ToolView*> toolViews;
public:
    void setupViews()
    {
        ToolView *view = new ToolView();
        view->origin = transformedFloat2(0.0, 0.0);
        view->scale = float2(0.16, 0.8) * scale;
        view->setToolType(DrawBezier);
        toolViews.push_back(view);
    }
    
    // draws the contents of the window
    bool draw();
    
    // all functions inherited from window, need to specify non-virtual and implement
    bool respondToMouseEvent(int button, int state, float2 point);
    bool respondToKeyboardEvent(unsigned char c);
};

#endif /* defined(__curves__ToolWindow__) */
