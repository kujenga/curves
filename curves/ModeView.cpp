//
//  ModeView.cpp
//  curves
//
//  Created by Aaron Taylor on 10/9/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "ModeView.h"


void ModeView::draw()
{
    View::draw();
    
    char buf[BUFSIZ];
    
    // hardcoded images for each tool type
    switch (applicationStateManager->getEditMode()) {
        case CreateMode:
            snprintf(buf, sizeof(buf), "Create");
            break;
        case ModifyMode:
            snprintf(buf, sizeof(buf), "Modify");
            break;
        case DestroyMode:
            snprintf(buf, sizeof(buf), "Destroy");
            break;
        case SelectMode:
            snprintf(buf, sizeof(buf), "Select");
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