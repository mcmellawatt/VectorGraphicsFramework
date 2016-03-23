#include "BitmapIteratorDecorator.h"
#include "Color.h"
#include "Doubleword.h"

BitmapIteratorDecorator::BitmapIteratorDecorator(const HBitmapIterator& originalIterator) :
myOriginalIterator(originalIterator)
{
}

BitmapIteratorDecorator::~BitmapIteratorDecorator()
{
}

void BitmapIteratorDecorator::nextScanLine()
{
    myOriginalIterator->nextScanLine();
}

bool BitmapIteratorDecorator::isEndOfImage() const
{
    return myOriginalIterator->isEndOfImage();
}

void BitmapIteratorDecorator::nextPixel()
{
    myOriginalIterator->nextPixel();
}

bool BitmapIteratorDecorator::isEndOfScanLine() const
{
    return myOriginalIterator->isEndOfScanLine();
}

int BitmapIteratorDecorator::getBitmapWidth() const
{
    return myOriginalIterator->getBitmapWidth();
}

int BitmapIteratorDecorator::getBitmapHeight() const
{
    return myOriginalIterator->getBitmapHeight();
}
