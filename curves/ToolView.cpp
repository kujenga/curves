//
//  ToolView.cpp
//  curves
//
//  Created by Aaron Taylor on 10/9/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "ToolView.h"

void ToolView::draw()
{
    View::draw();
    
    char buf[BUFSIZ];
    
    // hardcoded images for each tool type
    switch (viewToolType) {
        case DrawBezier:
            snprintf(buf, sizeof(buf), "Bezier");
            break;
        case DrawLagrange:
            snprintf(buf, sizeof(buf), "Lagrange");
            break;
        case DrawCircle:
            snprintf(buf, sizeof(buf), "Circle");
            break;
        case DrawPolyline:
            snprintf(buf, sizeof(buf), "Polyline");
            break;
            
        default:
            break;
    }
    
    glColor3d(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    float2 pos = transformedFloat2(-0.9, -0.2);
    glRasterPos2f(pos.x, pos.y);
    for (char *p = buf; *p; p++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);
    glPopMatrix();
}