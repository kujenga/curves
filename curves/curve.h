//
//  curve.h
//  curves
//
//  Created by Aaron Taylor on 9/18/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__curve__
#define __curves__curve__

#include <stdio.h>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
// Download glut from:
// http://www.opengl.org/resources/libraries/glut/
#include <GLUT/glut.h>

#include "float2.h"

// resolution of the drawing
#define STEP 0.01

#define TRACKER_SIZE 0.03

struct Color {
    float r;
    float g;
    float b;
    Color(float rVal, float gVal, float bVal) {
        r = rVal;
        g = gVal;
        b = bVal;
    }
};

class Curve {
protected:
    bool selected = false;
    
    void performTransformations();
    void inverseTransformations();
public:
    void setSelected(bool select) { selected = select; }
    // instantiated by subclasses to define curve
    virtual float2 getPoint(float t)=0;
    virtual float2 getDerivative(float t)=0;
    
    // methods for selection of the line
    float distFromCurve(float2 point);
    
    // curve functions that utilize virtual functions to draw the defined curve
    void draw();
    void drawTracker(float t);
    void drawTangent(float t);
    
    // variables for manipulating the curve
    Color lineColor = Color(1.0, 0.0, 1.0);
    Color selectedColor = Color(1.0, 0.0, 0.0);
    float2 translation = float2();
    float rotation = 0.0;
    float2 rotationOrigin = float2();
};

#endif /* defined(__curves__curve__) */
