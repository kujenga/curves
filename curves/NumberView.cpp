
//
//  NumberView.cpp
//  curves
//
//  Created by Aaron Taylor on 10/18/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "NumberView.h"

void NumberView::setupCurve(int d)
{
    digit = d;
//    if (curve ) {
//        delete curve;
//    }
    
    curve1 = new Bezier();
    for (int i = 0; i < PT_COUNT ; i++) {
        float2 pt = controlPoints[d][i]*0.005;
        curve1->addControlPoint(transformedFloat2(pt));
    }
}

void NumberView::draw()
{
    if (digit < 0) {
        return;
    }
    curve1->draw();
}