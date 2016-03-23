//
//  ComputeDimensions.h
//  Assignment1
//
//  Created by Chris Elderkin on 4/6/13.
//  Copyright (c) 2013 Chris Elderkin. All rights reserved.
//
#pragma once
#include "Point.h"
#include <climits>

namespace VG
{    
    // Function object to compute the width from a collection of Points
    class ComputeWidth
    {
    public:
        ComputeWidth() : myMax(INT_MIN), myMin(INT_MAX) { }
        void operator()(VG::Point point)
        {
            int pointX = point.getX();
            if (pointX > myMax)
            {
                myMax = pointX;
            }
            if (pointX < myMin)
            {
                myMin = pointX;
            }
        }
        // implicit type conversion to return width from for_each
        operator int()
        {
            return myMax - myMin;
        }
        
    private:
        int myMin;
        int myMax;
    };
    
    // Function object to find the height from a collection of Points
    class ComputeHeight
    {
    public:
        ComputeHeight() : myMax(INT_MIN), myMin(INT_MAX) { }
        void operator()(VG::Point point)
        {
            int pointY = point.getY();
            if (pointY > myMax)
            {
                myMax = pointY;
            }
            if (pointY < myMin)
            {
                myMin = pointY;
            }
        }
        // implicit type conversion to return width from for_each
        operator int()
        {
            return myMax - myMin;
        }
        
    private:
        int myMin;
        int myMax;
    };
}