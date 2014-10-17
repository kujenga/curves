//
//  hermiteinterp.cpp
//  curves
//
//  Created by Aaron Taylor on 10/12/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "hermiteinterp.h"

void HermiteInterp::addControlPoint(float2 newPoint)
{
    controlPoints.push_back(newPoint);
    controlPoints.push_back(float2(0.2,0.2));
}

void HermiteInterp::drawControlPointTangents()
{
    // draw tangent points and lines to them
    int siz = (int)controlPoints.size();
    for (int i = 0; i < siz; i+=2) {
        float2 curP = controlPoints.at(i);
        float2 curT = controlPoints.at(i+1) + curP;
        
        glBegin(GL_LINE_STRIP);
        glLineWidth(0.1);
        glVertex2d(curP.x, curP.y);
        glVertex2d(curT.x, curT.y);
        glEnd();
    }
}

void HermiteInterp::drawControlPoints()
{
    performTransformations();
    // inverse of line colors for markers
    if (selected) {
        glColor3d(1.0-selectedColor.r, 1.0-selectedColor.g, 1.0-selectedColor.b);
    } else {
        glColor3d(1.0-lineColor.r, 1.0-lineColor.g, 1.0-lineColor.b);
    }
    drawControlPointTangents();
    // draw points at control points
    int siz = (int)controlPoints.size();
    float2 last;
    for (int i = 0; i < siz; i++) {
        glBegin(GL_POLYGON);
        // inverse of line colors for markers
        if (selected) {
            glColor3d(1.0-selectedColor.r, 1.0-selectedColor.g, 1.0-selectedColor.b);
        } else {
            glColor3d(1.0-lineColor.r, 1.0-lineColor.g, 1.0-lineColor.b);
        }
        float2 cur = controlPoints.at(i);
        // tangent points are at odd indicies, move them if so
        if (i%2 != 0) {
            glColor3d(1.0, 0.0, 0.0);
            cur += last;
        }
        glVertex2d(cur.x - TRACKER_SIZE, cur.y);
        glVertex2d(cur.x, cur.y + TRACKER_SIZE);
        glVertex2d(cur.x + TRACKER_SIZE, cur.y);
        glVertex2d(cur.x, cur.y - TRACKER_SIZE);
        glEnd();
        last = cur;
    }
    inverseTransformations();
}

int HermiteInterp::currentControlPoint(float2 test)
{
    float2 last;
    for (int i = 0; i < controlPoints.size(); i++) {
        float2 cur = controlPoints.at(i);
        // tangent points are at odd indicies, move them if so
        if (i%2 != 0) {
            cur += last;
        }
        if (pointMatch(cur, test)) {
            return i;
        }
        last = cur;
    }
    return -1;
}

void HermiteInterp::moveControlPoint(int i, float2 pos)
{
    // adjusts tangent points
    if (i%2 != 0) {
        pos -= controlPointVectorElement(i-1);
    }
    Freeform::moveControlPoint(i, pos);
}

float2 cubicHermiteSplineFunc(float t, float2 p0, float2 m0, float2 p1, float2 m1)
{
    float h00 =  2.0*t*t*t - 3.0*t*t + 1.0;
    float h10 =      t*t*t - 2.0*t*t - t;
    float h01 = -2.0*t*t*t + 3.0*t*t;
    float h11 =      t*t*t -     t*t;

    //    printf("numPoints: %f, curPoint: %i, t: %f, ts: %f\n",numPoints, curPoint, t, ts);
    return p0*h00 + (m0)*h10 + p1*h01 + (m1)*h11;
}

float2 HermiteInterp::getPoint(float t)
{
    float numPoints = (float)controlPointVectorSize();
    if (controlPointVectorSize() < 4) {
        return controlPoints.at(0);
    }
    int curPoint = (int)floorf(t * (numPoints/2-1));
    float2 p0 = controlPointVectorElement(curPoint);
    float2 m0 = controlPointVectorElement(curPoint+1);
    float2 p1 = controlPointVectorElement(curPoint+2);
    float2 m1 = controlPointVectorElement(curPoint+3);
    
    numPoints /= 2;
    // scale t to the current subdivision
    float ts = (t - (curPoint/numPoints)) * numPoints * 0.5;
    
    return cubicHermiteSplineFunc(ts, p0, m0, p1, m1);
}

float2 HermiteInterp::getDerivative(float t)
{
    return float2();
}