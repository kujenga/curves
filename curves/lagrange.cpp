//
//  lagrange.cpp
//  curves
//
//  Created by Aaron Taylor on 10/1/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "lagrange.h"

Lagrange::Lagrange(const Freeform& previous)
{
//    const int siz = previous.controlPointVectorSize()
//    for (int i = 0; i < siz; i++) {
//        controlPoints.push_back(previous.controlPointVectorElement(i));
//        knots.push_back(1.0);
//    }
//    rescaleKnots();
}

void Lagrange::rescaleKnots()
{
    for (int i = 0; i < knots.size(); i++) {
        knots.at(i) = (float)i / (float)(fmax(knots.size()-1,1.0));
    }
}

void Lagrange::addControlPoint(float2 p)
{
    controlPoints.push_back(p);
    knots.push_back(1.0);
    // scale the knots again with new length
    rescaleKnots();
}

double Lagrange::lagrange(int i, double t) {
    double ln = 1.0;
    for (int j = 0; j < knots.size(); j++) {
        if (j != i) {
            ln *= t - knots.at(j);
        }
    }
    double ld = 1.0;
    for (int j = 0; j < knots.size(); j++) {
        if (j != i) {
            ld *= knots.at(i) - knots.at(j);
        }
    }
    double l = ln/ld;
    return l;
}

float2 Lagrange::getPoint(float t)
{
    float2 r(0.0, 0.0);
    // for every control point
    // compute weight using the Lagrange summation formula
    // add control point to r, weighted
    int siz = (int)controlPoints.size();
    for (int i = 0; i < siz; i++) {
        float2 ri = controlPoints.at(i);
        ri *= lagrange(i, t);
        r += ri;
    }
    return r;
}

float2 Lagrange::getDerivative(float t)
{
    return float2();
}