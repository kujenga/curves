//
//  WindowManager.cpp
//  curves
//
//  Created by Aaron Taylor on 10/6/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "WindowManager.h"

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>


void WindowManager::onKeyboard(unsigned char c, int x, int y)
{
    for (int i = (int)windowStack.size()-1; i >= 0; i--) {
        Window* window = windowStack.at(i);
        bool stopResponding = window->respondToKeyboardEvent(c);
        if (stopResponding) {
            return;
        }
    }
}

void WindowManager::onMove(float2 point) {
    for (int i = (int)windowStack.size()-1; i >= 0; i--) {
        Window* window = windowStack.at(i);
        bool stopResponding = window->respondToMoveEvent(point);
        if (stopResponding) {
            return;
        }
    }

}

void WindowManager::onMouse(int button, int state, float2 point) {
    for (int i = (int)windowStack.size()-1; i >= 0; i--) {
        Window* window = windowStack.at(i);
        bool stopResponding = window->respondToMouseEvent(button, state, point);
        if (stopResponding) {
            return;
        }
    }

}

void WindowManager::onIdle()
{
//    glutPostRedisplay();
}

void WindowManager::onDisplay()
{
    // drawing happens back to front, unlike event passing
    for (int i = 0; i < windowStack.size(); i++) {
        Window* window = windowStack.at(i);
        bool stopResponding = window->draw();
        if (stopResponding) {
            return;
        }
    }
}

// controls popping and pushing of windows from the manager
void WindowManager::pushWindow(Window* window)
{
    windowStack.push_back(window);
}

Window* WindowManager::popWindow()
{
    Window *back = windowStack.back();
    windowStack.pop_back();
    return back;
}



