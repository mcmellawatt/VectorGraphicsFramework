#pragma once

#include "BitmapIteratorDecorator.h"

class ColorInversionDecorator : public BitmapIteratorDecorator
{
public:
    ColorInversionDecorator(
        const HBitmapIterator& originalIterator);

    virtual Color getColor() const;
};
