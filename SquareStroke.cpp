#include "SquareStroke.h"
#include "SquarePen.h"
SquareStroke::SquareStroke(const int& size, const Color& color) : mySize(size), myColor(color) {}

void SquareStroke::setSize(int size)
{
    mySize = size;
}

int SquareStroke::getSize() const
{
    return mySize;
}

void SquareStroke::setColor(const Color& color)
{
    myColor = color;
}

Color SquareStroke::getColor() const
{
    return myColor;
}

HPen SquareStroke::createPen(const HCanvas& canvas)
{
	return HPen(new SquarePen(canvas,getSize(),getColor()));
}