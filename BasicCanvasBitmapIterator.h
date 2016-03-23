#pragma once

#include "IBitmapIterator.h"
#include "ICanvas.h"
#include "Point.h"

class BasicCanvasBitmapIterator : public IBitmapIterator
{
public:
    BasicCanvasBitmapIterator(const ICanvas& canvas);
    virtual ~BasicCanvasBitmapIterator() { }

    virtual void nextScanLine();
    virtual bool isEndOfImage() const;
    virtual void nextPixel();
    virtual bool isEndOfScanLine() const;
    virtual Color getColor() const;
    
    virtual int getBitmapWidth() const;
    virtual int getBitmapHeight() const;

private:
    const ICanvas& myCanvas;
    VG::Point myCurrentPoint;
};
