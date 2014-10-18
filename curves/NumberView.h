//
//  NumberView.h
//  curves
//
//  Created by Aaron Taylor on 10/18/14.
//  Copyright (c) 2014 Aaron Taylor. All rights reserved.
//

#ifndef __curves__NumberView__
#define __curves__NumberView__

#include <stdio.h>

#include "View.h"

class NumberView : public View {
    
public:
    int displayNum = 0;
    void draw();
};

#endif /* defined(__curves__NumberView__) */
