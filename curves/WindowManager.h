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

#include "Window.h"

class WindowManager
{
    
public:
    // controls popping and pushing of windows from the manager
    void pushWindow(Window* window);
    Window* popWindow();
};

#endif /* defined(__curves__WindowManager__) */
