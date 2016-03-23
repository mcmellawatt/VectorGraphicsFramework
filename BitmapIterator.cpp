//
//  BitmapIterator.cpp
//  DecoderExample
//
//  Created by Chris Elderkin on 5/15/13.
//  Copyright (c) 2013 Chris Elderkin. All rights reserved.
//

#include "BitmapIterator.h"

BitmapIterator::BitmapIterator()
{
}

BitmapIterator::BitmapIterator(const HBitmap& bitmap) :
myBitmap(bitmap),
myScanLine(bitmap->begin()),
myColor(myScanLine->begin())
{
}

void BitmapIterator::nextScanLine()
{
    ++myScanLine;
    if (myScanLine != myBitmap->end())
    {
        myColor = myScanLine->begin();
    }
}

bool BitmapIterator::isEndOfImage() const
{
    return myScanLine == myBitmap->end();
}

void BitmapIterator::nextPixel()
{
    ++myColor;
}

bool BitmapIterator::isEndOfScanLine() const
{
    return myColor == myScanLine->end();
}

Color BitmapIterator::getColor() const
{
    return *myColor;
}

int BitmapIterator::getBitmapHeight() const
{
    return myBitmap->getHeight();
}

int BitmapIterator::getBitmapWidth() const
{
    return myBitmap->getWidth();
}
