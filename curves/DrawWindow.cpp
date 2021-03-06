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
#include "polyline.h"
#include "bezier.h"
#include "lagrange.h"
#include "catmullclark.h"
#include "catmullrom.h"
#include "hermiteinterp.h"

// defaults to not handling the mouse
bool DrawWindow::respondToMouseEvent(int button, int state, float2 point)
{
    EditMode appEditMode = Window::appStateManager->getEditMode();
    
    /////////////////////////////
    // Creating new curves
    /////////////////////////////
    switch (appEditMode) {
        case CreateMode: {
            if (state == GLUT_UP) {
                Curve *curve;
                switch (Window::appStateManager->getToolType()) {
                    case DrawBezier:
                        curve = new Bezier();
                        static_cast<Bezier*>(curve)->addControlPoint(point);
                        break;
                        
                    case DrawLagrange:
                        curve = new Lagrange();
                        static_cast<Lagrange*>(curve)->addControlPoint(point);
                        break;
                        
                    case DrawCircle:
                        curve = new Circle();
                        // default radius of 0.25 for now
                        static_cast<Circle*>(curve)->setValues(point, 0.25);
                        break;
                        
                    case DrawPolyline:
                        curve = new Polyline;
                        static_cast<Polyline*>(curve)->addControlPoint(point);
                        break;
                        
                    case DrawCatmullClark:
                        curve = new CatmullClark;
                        static_cast<CatmullClark*>(curve)->addControlPoint(point);
                        break;
                        
                    case DrawCatmullRom:
                        curve = new CatmullRom;
                        static_cast<CatmullRom*>(curve)->addControlPoint(point);
                        break;
                        
                    case DrawHermiteInterp:
                        curve = new HermiteInterp;
                        static_cast<HermiteInterp*>(curve)->addControlPoint(point);
                        break;
                        
                    default:
                        break;
                        
                }
                if (curve != nullptr) {
                    appStateManager->curves.push_back(curve);
                    appStateManager->activeCurve()->setSelected(false);
                    curve->setSelected(true);
                    appStateManager->activeCurveIndex = (int)appStateManager->curves.size() - 1;
                    glutPostRedisplay();
                    Window::appStateManager->setEditMode(ModifyMode);
                    return true;
                }
            }
            break;
        }
            
        ///////////////////////////////
        // Select an Existing Curves
        ///////////////////////////////
        case SelectMode: {
            for (int i = 0; i < appStateManager->curves.size(); i++) {
                Curve *c = dynamic_cast<Curve*>(appStateManager->curves.at(i));
                if (free != nullptr) {
                    float dist = c->distFromCurve(point);
                    if (dist < SELECTION_DIST) {
                        appStateManager->setToActiveCurve(i);
                        appStateManager->setEditMode(ModifyMode);
                        return true;
                    }
                }
            }
            break;
        }
            
        ///////////////////////////////
        // Modify Existing Curves
        ///////////////////////////////
        case ModifyMode: {
            if (state == GLUT_DOWN) {
                Freeform *free = dynamic_cast<Freeform*>(appStateManager->activeCurve());
                if (free != nullptr) {
                    
                    int existingIndex = free->currentControlPoint(point);
                    if (existingIndex != -1) {
                        appStateManager->isDragging = true;
                        appStateManager->activePointIndex = existingIndex;
                    }
                    else {//if (button == GLUT_RIGHT_BUTTON) {
                        free->addControlPoint(point);
                    }
                    glutPostRedisplay();
                    return true;
                }
            } else if (state == GLUT_UP) {
                appStateManager->isDragging = false;
                // catmull clark needs to be recomputed, but it is too expensive to do it on every move of the point
                CatmullClark *cc = dynamic_cast<CatmullClark*>(appStateManager->activeCurve());
                if (cc != nullptr) {
                    cc->recomputeHolder(4);
                    glutPostRedisplay();
                }
                appStateManager->activePointIndex = -1;
            }
            break;
        }
        
            
        ///////////////////////////////
        // Destroy Curves or points on them (not fully functional)
        ///////////////////////////////
        case DestroyMode: {
            if (state == GLUT_UP) {
                Freeform *free = dynamic_cast<Freeform*>(appStateManager->curves.at(appStateManager->activeCurveIndex));
                if (free != nullptr) {
                    int existingIndex = free->currentControlPoint(point);
                    if (existingIndex != -1) {
                        free->deleteControlPoint(existingIndex);
                        // delete curves with fewer than 1 control point
                        if (free->controlPointVectorSize() < 1) {
                            appStateManager->deleteActiveCurve();
                        }
                    }
                    glutPostRedisplay();
                    return true;
                }
            }
            break;
        }
            
        default:
            break;
    }
    return false;
}

// defaults to not handling the move
bool DrawWindow::respondToMoveEvent(float2 point)
{
    if (appStateManager->isDragging && appStateManager->activePointIndex >= -1) {
        // dynamic cast to freeform curve which has movable points
        Freeform *free = dynamic_cast<Freeform*>(appStateManager->activeCurve());
        if (free != nullptr) {
            free->moveControlPoint(appStateManager->activePointIndex, point);
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
    
    for (int i = 0; i < appStateManager->curves.size(); i++) {
        Curve* curve = appStateManager->curves.at(i);
        //c.setValues(0.3, 0.0, 0.5);
        glColor3d(1.0, 1.0, 1.0);
        curve->draw();
        
        if (appStateManager->showTrackers) {
            // draws time-animated tracker point
            int t = glutGet(GLUT_ELAPSED_TIME);
            float drawt = (float)(t%10000) / 10000.0;
            curve->drawTracker(drawt);
            curve->drawTangent(drawt);
        }
        
        Freeform *free = dynamic_cast<Freeform*>(appStateManager->curves.at(appStateManager->activeCurveIndex));
        if (free != nullptr) {
            free->drawControlPoints();
        }
    }
    return false;
}

bool DrawWindow::draw()
{
    // draws a checkered background
    bool wb = true;
    float step = 0.05;
    glColor3d(0.9, 0.9, 0.9);
    for (float x = -1.0; x < 0.99; x += step) {
        for (float y = -1.0; y < 0.99; y += step) {
            glBegin(GL_POLYGON);
            if (wb) {
                glVertex2d(x, y);
                glVertex2d(x, y+step);
                glVertex2d(x+step, y+step);
                glVertex2d(x+step, y);
                glEnd();
            }
            wb = !wb;
        }
        wb = !wb;
    }
    
    for (int i = 0; i < appStateManager->curves.size(); i++) {
        Curve *cur = appStateManager->curves.at(i);
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
    
    return false;
}
