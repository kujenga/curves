
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
    curve2 = new Bezier();
    curve3 = new Bezier();
    curve4 = new Bezier();
    for (int i = 0; i < PT_COUNT ; i++) {
        float2 pt = (controlPoints[d][i]*float2(0.005, -0.005)) + float2(0.0, 1.0);
        if (i <= 3) {
            curve1->addControlPoint(transformedFloat2(pt));
        }
        if (i >= 3 && i <= 7) {
            curve2->addControlPoint(transformedFloat2(pt));
        }
        if (i >= 6 && i <= 9) {
            curve3->addControlPoint(transformedFloat2(pt));
        }
        if (i >= 9 && i <= 12) {
            curve4->addControlPoint(transformedFloat2(pt));
        }
    }
}

void NumberView::draw()
{
    if (digit < 0) {
        return;
    }
    curve1->draw();
    curve2->draw();
    curve3->draw();
    curve4->draw();
}