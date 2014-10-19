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
#include "NumberView.h"

class ToolWindow : public Window {
    std::vector<ToolView*> toolViews;
    NumberView *nView = new NumberView();
    
public:
    void setupViews();
    
    // draws the contents of the window
    bool draw();
    
    // all functions inherited from window, need to specify non-virtual and implement
    bool respondToMouseEvent(int button, int state, float2 point);
    bool respondToKeyboardEvent(unsigned char c);
};

#endif /* defined(__curves__ToolWindow__) */
