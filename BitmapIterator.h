//
//  BitmapIterator.h
//  DecoderExample
//
//  Created by Chris Elderkin on 5/15/13.
//  Copyright (c) 2013 Chris Elderkin. All rights reserved.
//
#pragma once

#include "IBitmapIterator.h"
#include "Bitmap.h"

class BitmapIterator : public IBitmapIterator
{
public:
    BitmapIterator();
    BitmapIterator(const HBitmap& bitmap);
    
    virtual void nextScanLine();
    virtual bool isEndOfImage() const;
    virtual void nextPixel();
    virtual bool isEndOfScanLine() const;
    virtual Color getColor() const;
    
    virtual int getBitmapWidth() const;
    virtual int getBitmapHeight() const;
    
private:
    HBitmap myBitmap;
    Bitmap::ScanLineIterator myScanLine;
    Bitmap::ColorIterator myColor;
};
