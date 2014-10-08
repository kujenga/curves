//
//  DrawWindow.cpp
//  curves
//
//  Created by Aaron Taylor on 10/6/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "DrawWindow.h"

#include "freeform.h"

#include "circle.h"
#include "bezier.h"
#include "lagrange.h"

// defaults to not handling the mouse
bool DrawWindow::respondToMouseEvent(int button, int state, float2 point)
{
    EditMode appEditMode = Window::applicationStateManager->getEditMode();
    
    if (appEditMode == CreateMode) {
        if (state == GLUT_UP) {
            Curve *curve;
            switch (Window::applicationStateManager->getToolType()) {
                case DrawBezier:
                    curve = new Bezier();
                    static_cast<Freeform*>(curve)->addControlPoint(point);
                    break;
                case DrawLagrange:
                    curve = new Lagrange();
                    static_cast<Freeform*>(curve)->addControlPoint(point);
                    break;
                case DrawCircle:
                    curve = new Circle();
                    // default radius of 0.25 for now
                    static_cast<Circle*>(curve)->setValues(point, 0.25);
                    break;
                    
                case DrawPolyline:
                    curve = nullptr;
                    // default radius of 0.25 for now
                    //static_cast<Circle*>(curve)->setValues(point, 0.25);
                    break;
                    
                default:
                    break;
            }
            if (curve != nullptr) {
                curves.push_back(curve);
                activeCurveIndex = (int)curves.size() - 1;
                glutPostRedisplay();
                Window::applicationStateManager->setEditMode(ModifyMode);
                return true;
            }
        }
    } else if (appEditMode == ModifyMode) {
        if (state == GLUT_DOWN) {
            Freeform *free = dynamic_cast<Freeform*>(curves.at(activeCurveIndex));
            if (free != nullptr) {
                int existingIndex = free->currentControlPoint(point);
                if (existingIndex != -1) {
                    isDragging = true;
                    activePointIndex = existingIndex;
                } else {//if (button == GLUT_RIGHT_BUTTON) {
                    free->addControlPoint(point);
                }
                glutPostRedisplay();
                return true;
            }
        } else if (state == GLUT_UP) {
            isDragging = false;
            activePointIndex = -1;
        }

    } else if (appEditMode == DestroyMode) {
        if (state == GLUT_UP) {
            Freeform *free = dynamic_cast<Freeform*>(curves.at(activeCurveIndex));
            if (free != nullptr) {
                int existingIndex = free->currentControlPoint(point);
                if (existingIndex != -1) {
                    free->deleteControlPoint(existingIndex);
                }
                glutPostRedisplay();
                return true;
            }
        }
    }
        return false;
}

// defaults to not handling the move
bool DrawWindow::respondToMoveEvent(float2 point)
{
    if (isDragging && activePointIndex >= -1) {
        // dynamic cast to freeform curve which has movable points
        Freeform *free = dynamic_cast<Freeform*>(curves.at(activeCurveIndex));
        if (free != nullptr) {
            free->moveControlPoint(activePointIndex, point);
            glutPostRedisplay();
            // absorb the motion as dragging a point should not affect windows beneath
            return true;
        }
    }
    return false;
}

bool DrawWindow::respondToDisplayEvent()
{
    glClearColor(0.4f, 0.7f, 0.9f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (int i = 0; i < curves.size(); i++) {
        Curve* curve = curves.at(i);
        //c.setValues(0.3, 0.0, 0.5);
        glColor3d(1.0, 1.0, 1.0);
        curve->draw();
        
        // draws time-animated tracker point
        int t = glutGet(GLUT_ELAPSED_TIME);
        float drawt = (float)(t%10000) / 10000.0;
        curve->drawTracker(drawt);
        curve->drawTangent(drawt);
        
        Freeform *free = dynamic_cast<Freeform*>(curves.at(activeCurveIndex));
        if (free != nullptr) {
            free->drawControlPoints();
        }
    }
    return false;
}

bool DrawWindow::draw()
{
    for (int i = 0; i < curves.size(); i++) {
        Curve *cur = curves.at(i);
        cur->draw();
        Freeform *free = dynamic_cast<Freeform*>(cur);
        if (free != nullptr) {
            free->drawControlPoints();
        }
        
        int t = glutGet(GLUT_ELAPSED_TIME);
        float drawt = (float)(t%10000) / 10000.0;
        cur->drawTracker(drawt);
        cur->drawTangent(drawt);
    }
    
    glBegin(GL_POLYGON);
    
    glColor3d(0.9f, 0.1f, 0.3f);
    glVertex2d(-1.0, -1.0);
    glColor3d(0.5f, 0.7f, 0.3f);
    for (int i = -10; i < 10; i++) {
        i%2 == 0 ? glVertex2d(0.1*i, -0.8) : glVertex2d(0.1*i, -0.5);
    }
    glColor3d(0.9f, 0.7f, 0.3f);
    glVertex2d(1.0, -1.0);
    
    glEnd();
    return false;
}
