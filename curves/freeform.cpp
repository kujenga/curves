//
//  freeform.cpp
//  curves
//
//  Created by Aaron Taylor on 10/1/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "freeform.h"

#define POINT_BUFFER 0.05

///////////////////////////////////////////////////
// CONSTRUCTORS
///////////////////////////////////////////////////

//Freeform::Freeform(void)
//{
//    
//}
//
//Freeform::Freeform(const Freeform& previous)
//{
//    controlPoints = previous.controlPoints;
//}

///////////////////////////////////////////////////
// DRAWING
///////////////////////////////////////////////////

void Freeform::drawControlPoints()
{
    // draw points at control points
    int siz = (int)controlPoints.size();
    for (int i = 0; i < siz; i++) {
        glBegin(GL_POLYGON);
        glColor3d(0.0, 1.0, 0.0);
        float2 cur = controlPoints.at(i);
        glVertex2d(cur.x - TRACKER_SIZE, cur.y);
        glVertex2d(cur.x, cur.y + TRACKER_SIZE);
        glVertex2d(cur.x + TRACKER_SIZE, cur.y);
        glVertex2d(cur.x, cur.y - TRACKER_SIZE);
        glEnd();
    }
}

///////////////////////////////////////////////////
// POINT MODIFICATION
///////////////////////////////////////////////////

bool pointMatch(float2 f1, float2 f2)
{
    float dist = sqrtf(powf(f1.x - f2.x, 2.0) + powf(f1.y - f2.y, 2.0));
    if (dist < POINT_BUFFER) return true;
    return false;
}

void Freeform::moveControlPoint(int i, float2 pos)
{
    controlPoints.at(i) = pos;
}

int Freeform::currentControlPoint(float2 test)
{
    for (int i = 0; i < controlPoints.size(); i++) {
        float2 cur = controlPoints.at(i);
        if (pointMatch(cur, test)) {
            return i;
        }
    }
    return -1;
}