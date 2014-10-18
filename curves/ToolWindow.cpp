//
//  ToolWindow.cpp
//  curves
//
//  Created by Aaron Taylor on 10/6/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "ToolWindow.h"

void ToolWindow::setupViews()
{
    ToolType types[] = {DrawBezier, DrawLagrange, DrawPolyline, DrawCatmullClark, DrawHermiteInterp, DrawCatmullRom};
    for (int i = 0; i < 6; i++) {
        ToolView *tv = new ToolView();
        tv->origin = transformedFloat2(-0.85 + 0.25 * (float)i, 0.0);
        tv->scale = float2(0.1, 0.8) * scale;
        tv->setToolType(types[i]);
        toolViews.push_back(tv);
    }
}

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
        ToolView *tv = toolViews.at(i);
        if (appStateManager->getToolType() == tv->getToolType()) {
            tv->setSelected(true);
        }
        tv->draw();
    }
    return false;
}

bool ToolWindow::respondToMouseEvent(int button, int state, float2 point)
{
    if (pointWithinBounds(point)) {
        if (state == GLUT_UP) {
            // default of nonetype
            appStateManager->setToolType(NoneType);
            // iterates over buttons to see which one was clicked, if any
            for (int i = 0; i < toolViews.size(); i++) {
                if (toolViews.at(i)->containsPoint(point)) {
                    toolViews.at(i)->setSelected(true);
                    // sets tool type in the state manager based on tool type of selected view
                    ToolType chosenType = toolViews.at(i)->getToolType();
                    if (chosenType != appStateManager->getToolType()) {
                        // if modes are changed, begin creating a new object
                        appStateManager->setEditMode(CreateMode);
                    }
                    appStateManager->setToolType(chosenType);
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
        // change application modes
        case 'n':
            Window::appStateManager->setEditMode(CreateMode);
            return true;
        case 'd':
            Window::appStateManager->setEditMode(DestroyMode);
            return true;
        case 's':
            Window::appStateManager->setEditMode(SelectMode);
            return true;
        case 'S':
            Window::appStateManager->showTrackers = !Window::appStateManager->showTrackers;
            return true;
        case ' ': {
            int newIndex = (appStateManager->activeCurveIndex+1) % appStateManager->curves.size();
            Window::appStateManager->setToActiveCurve(newIndex);
            return true;
        }
        
        // set line type
        case 'p':
            Window::appStateManager->setToolType(DrawPolyline);
            return true;
        case 'b':
            Window::appStateManager->setToolType(DrawBezier);
            return true;
        case 'l':
            Window::appStateManager->setToolType(DrawLagrange);
            return true;
            
        // perform transformations
        case 'r': {
            Curve* active = Window::appStateManager->activeCurve();
            active->rotation = 0.25*M_PI;
            return true;
        }
        case 't': {
            Curve* active = Window::appStateManager->activeCurve();
            active->translation = float2(0.5, 0.5);
            return true;
        }
        case 'f': {
            Curve* active = Window::appStateManager->activeCurve();
            active->filled = !active->filled;
            return true;
        }
            
        default:
            return false;
    }
}

