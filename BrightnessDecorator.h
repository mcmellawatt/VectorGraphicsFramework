#pragma once

#include "BitmapIteratorDecorator.h"

class BrightnessDecorator : public BitmapIteratorDecorator
{
public:
    BrightnessDecorator(const HBitmapIterator& originalIterator,
                        const int& brightnessAdjustment);

    void setBrightnessAdjustment(int brightnessAdjustment);
    int getBrightnessAdjustment() const;

    virtual Color getColor() const;

private:
    int myBrightnessAdjustment;
};
