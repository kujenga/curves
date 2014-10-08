//
//  ToolWindow.cpp
//  curves
//
//  Created by Aaron Taylor on 10/6/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "ToolWindow.h"

bool ToolWindow::draw()
{
    
    return false;
}

bool ToolWindow::respondToMouseEvent(int button, int state, float2 point)
{
    if (state == GLUT_UP) {
        
        return true;
    }
    return false;
}

bool ToolWindow::respondToKeyboardEvent(unsigned char c)
{
    switch (c) {
        case 'n':
            Window::applicationStateManager->setEditMode(CreateMode);
            return true;
            
        case 'd':
            Window::applicationStateManager->setEditMode(DestroyMode);
            return true;
            
        default:
            return false;
    }
}