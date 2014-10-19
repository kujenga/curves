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
#include "bezier.h"

#define PT_COUNT 13

class NumberView : public View {
    
    const float2 controlPoints[10][PT_COUNT] = {
        {float2(254.0,  47.0), float2(159.0, 84.0), float2(123.0, 158.0), float2(131.0, 258.0), float2(139.0, 358.0), float2(167.0, 445.0), float2(256.0, 446.0), float2(345.0, 447.0), float2(369.0, 349.0), float2(369.0, 275.0), float2(369.0, 201.0), float2(365.0, 81.0), float2(231.0, 75.0)},
        {float2(138.0, 180.0), float2(226.0, 99.0), float2(230.0, 58.0), float2(243.0, 43.0), float2(256.0, 28.0), float2(252.0, 100.0), float2(253.0, 167.0), float2(254.0, 234.0), float2(254.0, 194.0), float2(255.0, 303.0), float2(256.0, 412.0), float2(254.0, 361.0), float2(255.0, 424.0)},
        {float2(104.0, 111.0), float2(152.0, 55.0), float2(208.0, 26.0), float2(271.0, 50.0), float2(334.0, 74.0), float2(360.0, 159.0), float2(336.0, 241.0), float2(312.0, 323.0), float2(136.0, 454.0), float2(120.0, 405.0), float2(104.0, 356.0), float2(327.0, 393.0), float2(373.0, 414.0)},
        {float2( 96.0, 132.0), float2(113.0, 14.0), float2(267.0, 17.0), float2(311.0, 107.0), float2(355.0, 197.0), float2(190.0, 285.0), float2(182.0, 250.0), float2(174.0, 215.0), float2(396.0, 273.0), float2(338.0, 388.0), float2(280.0, 503.0), float2(110.0, 445.0), float2(93.0, 391.0)},
        {float2(374.0, 244.0), float2(249.0, 230.0), float2(192.0, 234.0), float2(131.0, 239.0), float2(70.0, 244.0), float2(142.0, 138.0), float2(192.0, 84.0), float2(242.0, 30.0), float2(283.0, -30.0), float2(260.0, 108.0), float2(237.0, 246.0), float2(246.0, 435.0), float2(247.0, 438.0)},
        {float2(340.0,  52.0), float2(226.0, 42.0), float2(153.0, 44.0), float2(144.0, 61.0), float2(135.0, 78.0), float2(145.0, 203.0), float2(152.0, 223.0), float2(159.0, 243.0), float2(351.0, 165.0), float2(361.0, 302.0), float2(371.0, 439.0), float2(262.0, 452.0), float2(147.0, 409.0)},
        {float2(301.0,  26.0), float2(191.0, 104.0), float2(160.0, 224.0), float2(149.0, 296.0), float2(138.0, 368.0), float2(163.0, 451.0), float2(242.0, 458.0), float2(321.0, 465.0), float2(367.0, 402.0), float2(348.0, 321.0), float2(329.0, 240.0), float2(220.0, 243.0), float2(168.0, 285.0)},
        {float2(108.0,  52.0), float2(168.0, 34.0), float2(245.0, 42.0), float2(312.0, 38.0), float2(379.0, 34.0), float2(305.0, 145.0), float2(294.0, 166.0), float2(283.0, 187.0), float2(243.0, 267.0), float2(231.0, 295.0), float2(219.0, 323.0), float2(200.0, 388.0), float2(198.0, 452.0)},
        {float2(243.0, 242.0), float2(336.0, 184.0), float2(353.0, 52.0), float2(240.0, 43.0), float2(127.0, 34.0), float2(143.0, 215.0), float2(225.0, 247.0), float2(307.0, 279.0), float2(403.0, 427.0), float2(248.0, 432.0), float2(93.0, 437.0), float2(124.0, 304.0), float2(217.0, 255.0)},
        {float2(322.0, 105.0), float2(323.0, 6.0), float2(171.0, 33.0), float2(151.0, 85.0), float2(131.0, 137.0), float2(161.0, 184.0), float2(219.0, 190.0), float2(277.0, 196.0), float2(346.0, 149.0), float2(322.0, 122.0), float2(298.0, 95.0), float2(297.0, 365.0), float2(297.0, 448.0)},
    };

    Bezier *curve1;
    Bezier *curve2;
    Bezier *curve3;
    Bezier *curve4;
    
    int digit = -1;
    
public:
    // setup the
    void setupCurve(int d);
    
    const int curDigit() { return digit; }
    
    void draw();
};

#endif /* defined(__curves__NumberView__) */
