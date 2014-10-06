//
//  Window.cpp
//  curves
//
//  Created by Aaron Taylor on 10/6/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "Window.h"

// defaults to not handling the mouse
bool Window::respondToMouseEvent(int button, int state, float2 point)
{
    return false;
}

// defaults to not handling the move
bool Window::respondToMoveEvent(float2 point)
{
    return false;
}

bool Window::respondToKeyboardEvent(unsigned char t)
{
    return false;
}