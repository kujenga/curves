//
//  main.cpp
//  curves
//
//  Created by Aaron Taylor on 9/18/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include <iostream>
#include <stdlib.h>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
// Download glut from:
// http://www.opengl.org/resources/libraries/glut/
#include <GLUT/glut.h>

#include "circle.h"
#include "crazycurve.h"
#include "bezier.h"
#include "lagrange.h"

// modes for creation and editing curves
typedef enum{
    circleMode,
    bezierMode,
    lagrangeMode
} curveMode;

typedef enum{
    createMode,
    destroyMode,
} editMode;

// used to generate random points
#define ARC4RANDOM_MAX 0x100000000
#define LITTLE_RAND ((double)arc4random() / ARC4RANDOM_MAX)*2.0 - 1.0

/////////////////////////////////////////////
// global variables
/////////////////////////////////////////////

Freeform *_curve = new Lagrange();

bool _movingPoint = false;
int _pointIndex = -1;

/////////////////////////////////////////////
// utility methods
/////////////////////////////////////////////

float2 pointFromPixels(int x, int y)
{
    
    int viewportRect[4];
    glGetIntegerv(GL_VIEWPORT, viewportRect);
    float2 p = float2(x * 2.0 / viewportRect[2] - 1.0,
                      -y * 2.0 / viewportRect[3] + 1.0);
    return p;
}

/////////////////////////////////////////////
// glut methods
/////////////////////////////////////////////

void onKeyboard(unsigned char c, int x, int y)
{
    switch (c) {
        case 'l':
            _curve = new Lagrange(*_curve);
            break;
            
        case 'b':
            _curve = new Bezier(*_curve);
            break;
            
        default:
            break;
    }
}

void onMove(int x, int y) {
    if (_movingPoint && _pointIndex >= -1) {
        _curve->moveControlPoint(_pointIndex, pointFromPixels(x, y));
        glutPostRedisplay();
    }
}

void onMouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        float2 selectedPoint = pointFromPixels(x, y);
        int existing = _curve->currentControlPoint(selectedPoint);
        if (existing != -1) {
            printf("found a point! state: %i",GLUT_DOWN);
            _movingPoint = true;
            _pointIndex = existing;
        } else {//if (button == GLUT_RIGHT_BUTTON) {
            _curve->addControlPoint(selectedPoint);
        }
        glutPostRedisplay();
    } else if (state == GLUT_UP) {
        _movingPoint = false;
        _pointIndex = -1;
    }
}

void onIdle()
{
    glutPostRedisplay();
}

void onDisplay()
{
    
    glClearColor(0.4f, 0.7f, 0.9f, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    

    //c.setValues(0.3, 0.0, 0.5);
    glColor3d(1.0, 1.0, 1.0);
    _curve->draw();
    _curve->drawControlPoints();
    
    // draws time-animated tracker point
    int t = glutGet(GLUT_ELAPSED_TIME);
    float drawt = (float)(t%10000) / 10000.0;
    _curve->drawTracker(drawt);
    _curve->drawTangent(drawt);
    
    glutSwapBuffers();
}

/////////////////////////////////////////////
// main function
/////////////////////////////////////////////

int main(int argc, char * argv[]) {
    // creates a circle (on the stack) and draws it
    for (int i = 0; i < 3; i++) {
        _curve->addControlPoint(float2(LITTLE_RAND, LITTLE_RAND));
    }
    
    glutInit(&argc, argv);
    glutInitWindowSize(480, 480);
    glutInitWindowPosition(100, 100);
    
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    glutCreateWindow("Dodge");
    
    glutDisplayFunc(onDisplay);
    glutIdleFunc(onIdle);
    glutMouseFunc(onMouse);
    glutMotionFunc(onMove);
    glutKeyboardFunc(onKeyboard);
    
    glutMainLoop();
    return 0;
}
