//
//  StateManager.cpp
//  curves
//
//  Created by Aaron Taylor on 10/9/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#include "StateManager.h"

void StateManager::setToActiveCurve(int pos)
{
    activeCurve()->setSelected(false);
    activeCurveIndex = pos;
    activeCurve()->setSelected(true);
}