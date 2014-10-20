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
    DrawCatmullClark,
    DrawCatmullRom,
    DrawHermiteInterp
} ToolType;

typedef enum{
    SelectMode,
    CreateMode,
    ModifyMode,
    DestroyMode,
} EditMode;

class StateManager {
    ToolType applicationToolType = DrawCatmullRom;
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
    // whether or not the curves should be filled
    bool shouldFill;
    
    // whether or not trackers should be displayed
    bool showTrackers;
    
    
    int curveCount() { return (int)curves.size(); }
    
    Curve* activeCurve() { return curves.at(activeCurveIndex); }
    void setToActiveCurve(int pos);
    void deleteActiveCurve() { curves.erase(curves.begin() + activeCurveIndex); }

    const ToolType getToolType() { return applicationToolType; }
    const EditMode getEditMode() { return applicationEditMode; }
    
    void setToolType(ToolType t) { applicationToolType = t; }
    void setEditMode(EditMode m) { applicationEditMode = m; }
};

#endif /* defined(__curves__StateManager__) */
