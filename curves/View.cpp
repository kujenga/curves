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

void View::draw(Color c)
{
    glBegin(GL_POLYGON);
    
    glColor3d(c.r, c.g, c.b);
    
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

void View::draw()
{
    Color c = Color(0.2, 1.0, 0.2);
    if (selected) {
        c = Color(0.2, 1.0, 1.0);
    }
    draw(c);
}