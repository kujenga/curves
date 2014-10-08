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
#include <GLUT/glut.h>

#include "WindowManager.h"
#include "StateManager.h"
#include "DrawWindow.h"
#include "ToolWindow.h"

// used to generate random points
#define ARC4RANDOM_MAX 0x100000000
#define LITTLE_RAND ((double)arc4random() / ARC4RANDOM_MAX)*2.0 - 1.0

/////////////////////////////////////////////
// global variables
/////////////////////////////////////////////

WindowManager *_mainWindowManager;
StateManager *_mainStateManager;

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
    _mainWindowManager->onKeyboard(c, x, y);
}

void onMove(int x, int y) {
    _mainWindowManager->onMove(pointFromPixels(x, y));
}

void onMouse(int button, int state, int x, int y) {
    _mainWindowManager->onMouse(button, state, pointFromPixels(x, y));
}

void onIdle()
{
    glutPostRedisplay();
}

void onDisplay()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    _mainWindowManager->onDisplay();
    glutSwapBuffers();
}

/////////////////////////////////////////////
// main function
/////////////////////////////////////////////

int main(int argc, char * argv[])
{
    // create window manager and push configured windows to its stack
    _mainWindowManager = new WindowManager();
    _mainStateManager = new StateManager();
    
    DrawWindow *dw = new DrawWindow();
    dw->setApplicationStateManager(_mainStateManager);
    _mainWindowManager->pushWindow(dw);
    
    ToolWindow *tw = new ToolWindow();
    tw->setApplicationStateManager(_mainStateManager);
    _mainWindowManager->pushWindow(tw);
    
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
