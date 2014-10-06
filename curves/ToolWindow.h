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

#include "Window.h"

class ToolWindow : public Window {
    
public:
    // draws the contents of the window
    bool draw();
    
    // all functions inherited from window, need to specify non-virtual and implement
};

#endif /* defined(__curves__ToolWindow__) */
