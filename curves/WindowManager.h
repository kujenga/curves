//
//  WindowManager.h
//  curves
//
//  Created by Aaron Taylor on 10/6/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__WindowManager__
#define __curves__WindowManager__

#include <stdio.h>
#include <vector>

#include "Window.h"

class WindowManager
{
    std::vector<Window*> windowStack;
    

public:
    // in-class GLUT responders
    void onKeyboard(unsigned char c, int x, int y);
    void onMove(float2 point);
    void onMouse(int button, int state, float2 point);
    void onIdle();
    void onDisplay();
    
    // controls popping and pushing of windows from the manager
    void pushWindow(Window* window);
    // returns the window popped fron the window stack. caller is responsible for memory management
    Window* popWindow();
};

#endif /* defined(__curves__WindowManager__) */
