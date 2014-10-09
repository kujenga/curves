//
//  ToolView.h
//  curves
//
//  Created by Aaron Taylor on 10/9/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__ToolView__
#define __curves__ToolView__

#include <stdio.h>

#include "View.h"
#include "StateManager.h"

class ToolView : public View {
    ToolType viewToolType;
public:
    void setToolType( ToolType tt ) { viewToolType = tt; }
    ToolType getToolType() { return viewToolType; }
    
    void draw();
};

#endif /* defined(__curves__ToolView__) */
