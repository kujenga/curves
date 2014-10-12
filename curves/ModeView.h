//
//  ModeView.h
//  curves
//
//  Created by Aaron Taylor on 10/9/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__ModeView__
#define __curves__ModeView__

#include <stdio.h>

#include "View.h"
#include "StateManager.h"

class ModeView : public View {
    
public:
    StateManager *applicationStateManager;
    void draw();
};

#endif /* defined(__curves__ModeView__) */
