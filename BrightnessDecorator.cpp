#include "BrightnessDecorator.h"
#include "Color.h"
#include "ranged_number.h"

BrightnessDecorator::BrightnessDecorator(
    const HBitmapIterator& originalIterator,
    const int& brightnessAdjustment)
    : BitmapIteratorDecorator(originalIterator),
    myBrightnessAdjustment(brightnessAdjustment)
{
}

void BrightnessDecorator::setBrightnessAdjustment(int myBrightnessAdjustment)
{
    myBrightnessAdjustment = myBrightnessAdjustment;
}

int BrightnessDecorator::getBrightnessAdjustment() const
{
    return myBrightnessAdjustment;
}

// Arithmetic with unsigned values can have wrap-around
// consequences, so we want to use int here.
typedef ranged_number<int, 0, 255> ColorComponent;

Color BrightnessDecorator::getColor() const
{
    const Color oldColor = myOriginalIterator->getColor();

    ColorComponent red(oldColor.getRed() +  myBrightnessAdjustment);
    ColorComponent green(oldColor.getGreen() + myBrightnessAdjustment);
    ColorComponent blue(oldColor.getBlue() + myBrightnessAdjustment);

    return Color(Binary::Byte(red), Binary::Byte(green), Binary::Byte(blue));			
}
