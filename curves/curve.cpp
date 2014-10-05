//
//  curve.cpp
//  curves
//
//  Created by Aaron Taylor on 9/18/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "curve.h"

void Curve::draw()
{
    glBegin(GL_LINE_STRIP);
    for (float t = 0; t < 1.0; t += STEP) {
        float2 cur = getPoint(t);
        glVertex2d(cur.x, cur.y);
    }
    glEnd();
}

void Curve::drawTracker(float t)
{
    glBegin(GL_POLYGON);
    glColor3d(1.0, 0.0, 0.0);
    float2 cur = getPoint(t);
    glVertex2d(cur.x - TRACKER_SIZE, cur.y);
    glVertex2d(cur.x, cur.y + TRACKER_SIZE);
    glVertex2d(cur.x + TRACKER_SIZE, cur.y);
    glVertex2d(cur.x, cur.y - TRACKER_SIZE);
    glEnd();
}

void Curve::drawTangent(float t)
{
    glBegin(GL_LINES);
    glColor3d(1.0, 0.0, 0.0);
    float2 curP = getPoint(t);
    float2 start = curP - getDerivative(t);
    float2 end = curP + getDerivative(t);
    glVertex2d(start.x, start.y);
    glVertex2d(end.x, end.y);
    glEnd();
}
