//
//  curve.cpp
//  curves
//
//  Created by Aaron Taylor on 9/18/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "curve.h"

#define DIST_STEPS 100

// non-optimized, maybe possible to use the tangent function to find normal intersection in O(1) time rather than O(n) for n points along the curve
float Curve::distFromCurve(float2 point)
{
    float minDist = 2.0;
    for (float t = 0.0; t < 1.0; t += (1.0/DIST_STEPS)) {
        float2 test = getPoint(t);
        //float2 testd = getDerivative(t);
        
        float2 curDistVec = test - point;
        // pythagorean theorem to calculate distance
        float curDist = sqrtf(powf(curDistVec.x, 2.0) + powf(curDistVec.y, 2.0));
        if (curDist < minDist) {
            minDist = curDist;
        }
    }
    return minDist;
}

void Curve::draw()
{
    glBegin(GL_LINE_STRIP);
    glTranslatef(translation.x, translation.y, 0.0);
    glRotatef(360.0*rotation/M_PI, rotationOrigin.x, rotationOrigin.y, 0.0);
    if (selected) {
        glColor3d(1.0, 1.0, 0.0);
    } else {
        glColor3d(1.0, 0.0, 1.0);
    }
    for (float t = 0; t < 1.0; t += STEP) {
        float2 cur = getPoint(t);
        glVertex2d(cur.x, cur.y);
    }
    glEnd();
}

void Curve::drawTracker(float t)
{
    glBegin(GL_POLYGON);
    glTranslatef(translation.x, translation.y, 0.0);
    glRotatef(360.0*rotation/M_PI, rotationOrigin.x, rotationOrigin.y, 0.0);
    
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
    glTranslatef(translation.x, translation.y, 0.0);
    glRotatef(360.0*rotation/M_PI, rotationOrigin.x, rotationOrigin.y, 0.0);
    glColor3d(1.0, 0.0, 0.0);
    float2 curP = getPoint(t);
    float2 start = curP - getDerivative(t);
    float2 end = curP + getDerivative(t);
    glVertex2d(start.x, start.y);
    glVertex2d(end.x, end.y);
    glEnd();
}
