//
//  View.cpp
//  curves
//
//  Created by Aaron Taylor on 10/9/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "View.h"

bool View::containsPoint(float2 point)
{
    bool horizontal = origin.x - scale.x < point.x && origin.x + scale.x > point.x;
    bool vertical = origin.y - scale.y < point.y && origin.y + scale.y > point.y;
    return horizontal && vertical;
}

void View::draw()
{
    glBegin(GL_POLYGON);
    
    if (selected) {
        glColor3d(0.2, 1.0, 1.0);
    } else {
        glColor3d(0.2, 1.0, 0.2);
    }
    float2 corner = transformedFloat2(-1.0, 1.0);
    glVertex2d(corner.x, corner.y);
    corner = transformedFloat2( 1.0,  1.0);
    glVertex2d(corner.x, corner.y);
    corner = transformedFloat2( 1.0, -1.0);
    glVertex2d(corner.x, corner.y);
    corner = transformedFloat2(-1.0, -1.0);
    glVertex2d(corner.x, corner.y);
    
    glEnd();
}