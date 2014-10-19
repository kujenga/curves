//
//  View.h
//  curves
//
//  Created by Aaron Taylor on 10/9/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__View__
#define __curves__View__

#include <stdio.h>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#include "curve.h"

class View {
protected:
    bool selected = false;
    
    float2 transformedFloat2(float x, float y)
    {
        return scale * float2(x, y) + origin;
    }
    
    float2 transformedFloat2(float2 p)
    {
        return scale * p + origin;
    }
public:
    float2 scale;
    float2 origin;
    
    bool containsPoint(float2 point);
    
    void setSelected(bool select) { selected = select; }
    
    virtual void draw();
};

#endif /* defined(__curves__View__) */
