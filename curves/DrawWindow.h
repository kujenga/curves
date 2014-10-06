//
//  DrawWindow.h
//  curves
//
//  Created by Aaron Taylor on 10/6/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__DrawWindow__
#define __curves__DrawWindow__

#include <stdio.h>
#include <vector>

#include "Window.h"

class DrawWindow : Window {
    
    std::vector<Curve*> curves;
    
public:
    // all functions inherited from window, need to specify non-virtual and implement
};

#endif /* defined(__curves__DrawWindow__) */
