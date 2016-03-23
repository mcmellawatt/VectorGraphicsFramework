#include "SquarePen.h"
#include "Point.h"

SquarePen::SquarePen(const HCanvas& canvas, int size, const Color& color) : myCanvas(canvas), mySize(size), myColor(color) {}

namespace 
{
	bool inRect(const VG::Point& p, int left, int upper, int right, int lower)
	{
		if (p.getX() < left || p.getX() >= right)
			return false;
		if (p.getY() < upper || p.getY() >= lower)
			return false;
		return true;
	}
}

void SquarePen::drawPoint(const VG::Point& point)
{
	VG::Point bottomLeftPoint = point;

	for (int i = 0; i < mySize; ++i)
	{
		for (int j = 0; j < mySize; ++j)
		{
			VG::Point nextPoint = bottomLeftPoint + VG::Point(i,j);

			if(inRect(nextPoint, 0, 0, myCanvas->getWidth(), myCanvas->getHeight()))
			{
				myCanvas->setPixelColor(nextPoint, myColor);
			}
		}
	}
}