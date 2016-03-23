#pragma once

#include "SharedPtr.h"

namespace Binary { class DoubleWord; }
class Color;

class IBitmapIterator
{
public:
    virtual ~IBitmapIterator() { }

    virtual void nextScanLine() = 0;
    virtual bool isEndOfImage() const = 0;
    virtual void nextPixel() = 0;
    virtual bool isEndOfScanLine() const = 0;
    virtual Color getColor() const = 0;
    
    virtual int getBitmapWidth() const = 0;
    virtual int getBitmapHeight() const = 0;
};

typedef Cst::SharedPtr<IBitmapIterator> HBitmapIterator;
