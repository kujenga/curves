//
//  curve.cpp
//  curves
//
//  Created by Aaron Taylor on 9/18/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "curve.h"

#define DIST_STEPS 100

void Curve::performTransformations()
{
    glTranslatef(translation.x, translation.y, 0.0);
    glRotatef(360.0*rotation/M_PI, rotationOrigin.x, rotationOrigin.y, 1.0);
}

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

///////////////////////////////////
// Drawing functions
///////////////////////////////////

// theory from: http://www.geometrictools.com/Documentation/TriangulationByEarClipping.pdf
// certain implementations based on: http://www.blackpawn.com/texts/pointinpoly/ (barycentric technique)

float dotProd(float2 a, float2 b)
{
    return a.x * b.x + a.y * b.y;
}

// questionable...
float2 crossProd(float2 a, float2 b)
{
    return float2(a.x * b.y, a.y * b.x);
}

// unused, cross products don't seem to make much sense for 2D vectors...
bool sameSide(float2 p1, float2 p2, float2 a, float2 b)
{
    float2 cp1 = crossProd((b-a), (p1-a));
    float2 cp2 = crossProd((b-a), (p2-a));
    float dp = dotProd(cp1, cp2);
    if (dp >= 0) {
        return true;
    }
    return false;
}

float signedArea(float2 a, float2 b, float2 c){
    //http://stackoverflow.com/questions/17173633/determine-if-vertex-is-convex-help-understanding
    //http://www.mathopenref.com/coordtrianglearea.html
    return (a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y)) / 2;
}

bool containsPoint(float2 a, float2 b, float2 c, float2 p)
{
    // Compute vectors
    float2 v0 = c - a;
    float2 v1 = b - a;
    float2 v2 = p - a;
    
    // Compute dot products
    float dot00 = dotProd(v0, v0);
    float dot01 = dotProd(v0, v1);
    float dot02 = dotProd(v0, v2);
    float dot11 = dotProd(v1, v1);
    float dot12 = dotProd(v1, v2);
    
    // Compute barycentric coordinates
    float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;
    
    // Check if point is in triangle
    return (u >= 0) && (v >= 0) && (u + v < 1);
}

void Curve::drawFilled(std::list<float2> pts, std::list<float2> cur)
{
    /*
     bi-directional curves:
     Compute the sum of all consecutive triangles around the edge of the shape, determine conterclockwise or clockwise nature based on whether the sum is negative or positive. Store this in a state of the curve and the signedArea of triangles must match that sign if they are to be drawn
     
     Still need to re-iterate over the curve to fill in internal ears (should already be handled, check existibg implementation)
     */
    
    bool validEar = true;
    std::list<float2>::const_iterator itr = pts.begin(), end = pts.end();
    std::list<float2>::const_iterator curItr = cur.begin();
    float2 fst = *(curItr++);
    float2 snd = *(curItr++);
    float2 trd = *(curItr++);
    float cursa = signedArea(fst, snd, trd);
    if (areaSum < 0 ? cursa >= 0 : cursa < 0 ) {
        validEar = false;
    } else {
        for ( ; itr != end; ++itr) {
            float2 p = *itr;
            if (p == fst || p == snd || p == trd) {
                continue;
            }
            if (containsPoint(fst, snd, trd, p)) {
                validEar = false;
                break;
            }
        }
    }
    // handle drawing if result indicates a valid ear
    if (validEar) {
        glPushMatrix();
        performTransformations();
        glBegin(GL_TRIANGLE_FAN);
        if (selected) {
            glColor3d(selectedColor.r, selectedColor.g, selectedColor.b);
        } else {
            glColor3d(lineColor.r, lineColor.g, lineColor.b);
        }
        glVertex2d(fst.x, fst.y);
        glVertex2d(snd.x, snd.y);
        glVertex2d(trd.x, trd.y);
        glEnd();
        glPopMatrix();
        
        cur.pop_front();
        cur.pop_front();
        cur.push_front(fst);
    } else {
        cur.pop_front();
    }
    if (cur.size() >= 3) {
        drawFilled(pts, cur);
    } else {
        return;
    }
}

void Curve::drawOutline()
{
    glPushMatrix();
    performTransformations();
    glBegin(GL_LINE_STRIP);
    if (selected) {
        glColor3d(selectedColor.r, selectedColor.g, selectedColor.b);
    } else {
        glColor3d(lineColor.r, lineColor.g, lineColor.b);
    }
    for (float t = 0; t < 1.0; t += STEP) {
        float2 cur = getPoint(t);
        glVertex2d(cur.x, cur.y);
    }
    glEnd();
    glPopMatrix();
}

void Curve::draw()
{
    // test code for containsPoint function
    static bool tested = false;
    if (!tested) {
        if (!containsPoint(float2(0, 0), float2(2,0), float2(1, 2), float2(1,1))) {
            puts("bad inside");
        }
        if (containsPoint(float2(0, 0), float2(2,0), float2(1, 2), float2(0,1))) {
            puts("bad outside left");
        }
        if (containsPoint(float2(0, 0), float2(2,0), float2(1, 2), float2(2,1))) {
            puts("bad outside right");
        }
        if (containsPoint(float2(0, 0), float2(2,0), float2(1, 2), float2(1,-1))) {
            puts("bad outside below");
        }
        tested = true;
    }
    
    if (filled) {
        std::list<float2> pts;
        //create DLL of all the points in the shape
        for (float t = 0; t < 1.0; t += STEP) {
            pts.push_back(getPoint(t));
        }
        
        areaSum = 0.0;
        std::list<float2>::const_iterator itr = pts.begin(), end = pts.end();
        while (itr != end) {
            float2 fst = *(itr++);
            if (itr == end) {
                break;
            }
            float2 snd = *(itr++);
            if (itr == end) {
                break;
            }
            float2 trd = *(itr++);
            if (itr == end) {
                break;
            }

            areaSum += signedArea(fst, snd, trd);
        }
        
        drawFilled(pts, pts);
    }
    drawOutline();

}

void Curve::drawTracker(float t)
{
    glPushMatrix();
    performTransformations();
    glBegin(GL_POLYGON);
    // inverse of line colors for markers
    if (selected) {
        glColor3d(1.0-selectedColor.r, 1.0-selectedColor.g, 1.0-selectedColor.b);
    } else {
        glColor3d(1.0-lineColor.r, 1.0-lineColor.g, 1.0-lineColor.b);
    }
    float2 cur = getPoint(t);
    glVertex2d(cur.x - TRACKER_SIZE, cur.y);
    glVertex2d(cur.x, cur.y + TRACKER_SIZE);
    glVertex2d(cur.x + TRACKER_SIZE, cur.y);
    glVertex2d(cur.x, cur.y - TRACKER_SIZE);
    glEnd();
    glPopMatrix();
}

void Curve::drawTangent(float t)
{
    glPushMatrix();
    performTransformations();
    glBegin(GL_LINES);
    // inverse of line colors for markers
    if (selected) {
        glColor3d(1.0-selectedColor.r, 1.0-selectedColor.g, 1.0-selectedColor.b);
    } else {
        glColor3d(1.0-lineColor.r, 1.0-lineColor.g, 1.0-lineColor.b);
    }
    float2 curP = getPoint(t);
    float2 start = curP - getDerivative(t);
    float2 end = curP + getDerivative(t);
    glVertex2d(start.x, start.y);
    glVertex2d(end.x, end.y);
    glEnd();
    glPopMatrix();
}
