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
#define TRACKER_SIZE 0.05

class Curve
{
    
public:
    // instantiated by subclasses to define curve
    virtual float2 getPoint(float t)=0;
    virtual float2 getDerivative(float t)=0;
    
    // curve functions that utilize virtual functions to draw the defined curve
    void draw();
    void drawTracker(float t);
    void drawTangent(float t);
};

#endif /* defined(__curves__curve__) */
