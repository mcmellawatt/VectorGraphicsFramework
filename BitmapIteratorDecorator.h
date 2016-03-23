#pragma once

#include "IBitmapIterator.h"

class BitmapIteratorDecorator : public IBitmapIterator
{
public:
    BitmapIteratorDecorator(const HBitmapIterator& originalIterator);
    virtual ~BitmapIteratorDecorator();

    virtual void nextScanLine();
    virtual bool isEndOfImage() const;
    virtual void nextPixel();
    virtual bool isEndOfScanLine() const;
    
    virtual int getBitmapWidth() const;
    virtual int getBitmapHeight() const;

protected:
    HBitmapIterator myOriginalIterator;
};
