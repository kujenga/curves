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
    glBegin(GL_POLYGON);
    
    glColor3d(0.2, 0.2, 0.2);
    float2 corner = transformedFloat2(-1.0, 1.0);
    glVertex2d(corner.x, corner.y);
    corner = transformedFloat2( 1.0,  1.0);
    glVertex2d(corner.x, corner.y);
    corner = transformedFloat2( 1.0, -1.0);
    glVertex2d(corner.x, corner.y);
    corner = transformedFloat2(-1.0, -1.0);
    glVertex2d(corner.x, corner.y);
    
    glEnd();
    
    for (int i = 0; i < toolViews.size(); i++) {
        toolViews.at(i)->draw();
    }
    return false;
}

bool ToolWindow::respondToMouseEvent(int button, int state, float2 point)
{
    if (pointWithinBounds(point)) {
        if (state == GLUT_UP) {
            // default of nonetype
            applicationStateManager->setToolType(NoneType);
            // iterates over buttons to see which one was clicked, if any
            for (int i = 0; i < toolViews.size(); i++) {
                if (toolViews.at(i)->containsPoint(point)) {
                    toolViews.at(i)->setSelected(true);
                    // sets tool type in the state manager based on tool type of selected view
                    ToolType chosenType = toolViews.at(i)->getToolType();
//                    if (chosenType != applicationStateManager->getToolType()) {
//                        // if modes are changed, begin creating a new object
//                        applicationStateManager->setEditMode(CreateMode);
//                    }
                    applicationStateManager->setToolType(chosenType);
                } else {
                    toolViews.at(i)->setSelected(false);
                }
            }
            return true;
        }
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