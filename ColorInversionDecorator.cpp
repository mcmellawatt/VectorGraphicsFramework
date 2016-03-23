#include "ColorInversionDecorator.h"
#include "Color.h"

ColorInversionDecorator::ColorInversionDecorator(const HBitmapIterator& originalIterator) :
BitmapIteratorDecorator(originalIterator)
{
}

Color ColorInversionDecorator::getColor() const
{
    const Color oldColor = myOriginalIterator->getColor();

    return Color(255 - oldColor.getRed(), 255 - oldColor.getGreen(), 255 - oldColor.getBlue());
}