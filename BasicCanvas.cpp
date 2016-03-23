#include "BasicCanvas.h"
#include "BasicCanvasBitmapIterator.h"

BasicCanvas::BasicCanvas(int width, int height, const Color& backgroundColor) : myWidth(width), myHeight(height), myBackgroundColor(backgroundColor) 
{ 
}

void BasicCanvas::setPixelColor(const VG::Point& point, const Color& color)
{
	myPixelMap.insert(std::make_pair(point,color));
}

Color BasicCanvas::getPixelColor(const VG::Point& location) const
{
	if(myPixelMap.find(location) != myPixelMap.end())
		return myPixelMap.find(location)->second;
	else
		return myBackgroundColor;
}

int BasicCanvas::getWidth() const
{
	return myWidth;
}

int BasicCanvas::getHeight() const
{
	return myHeight;
}

HBitmapIterator BasicCanvas::createBitmapIterator() const
{
	 return HBitmapIterator(new BasicCanvasBitmapIterator(*this));
}

Color BasicCanvas::getBackgroundColor() const
{
	return myBackgroundColor;
}

bool BasicCanvas::outOfRange(const VG::Point& point) const
{
	if (point.getX() < 0 || point.getX() >= myWidth)
		return true;
	if (point.getY() < 0 || point.getY() >= myHeight)
		return true;
	return false;
}