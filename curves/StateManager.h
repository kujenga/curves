//
//  StateManager.h
//  curves
//
//  Created by Aaron Taylor on 10/9/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__StateManager__
#define __curves__StateManager__

#include <stdio.h>
#include <vector>
#include "curve.h"

// modes for creation and editing curves
typedef enum {
    NoneType,
    DrawBezier,
    DrawLagrange,
    DrawCircle,
    DrawPolyline,
} ToolType;

typedef enum{
    SelectMode,
    CreateMode,
    ModifyMode,
    DestroyMode,
} EditMode;

class StateManager {
    ToolType applicationToolType = DrawBezier;
    EditMode applicationEditMode = CreateMode;
    
public:
    // all the curves created within the application
    std::vector<Curve*> curves;
    
    // index of the currently active curve
    int activeCurveIndex;
    // index of the currently active point along the curve
    int activePointIndex;
    // whether or not a point along the active curve is currently being dragged
    bool isDragging;
    
    Curve* activeCurve() { return curves.at(activeCurveIndex); }

    ToolType getToolType() { return applicationToolType; }
    EditMode getEditMode() { return applicationEditMode; }
    
    void setToolType(ToolType t) { applicationToolType = t; }
    void setEditMode(EditMode m) { applicationEditMode = m; }
};

#endif /* defined(__curves__StateManager__) */
