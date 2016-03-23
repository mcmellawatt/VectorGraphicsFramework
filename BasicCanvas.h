#pragma once

#include "ICanvas.h"
#include "Point.h"
#include "Color.h"
#include <map>

class BasicCanvas : public ICanvas
{
	typedef std::map<VG::Point, Color,VG::PointCompare> PixelMap;

public:
	BasicCanvas(int width, int height, const Color& backgroundColor = Color(0, 0, 0));

	virtual void setPixelColor(const VG::Point& location, const Color& color);
	virtual Color getPixelColor(const VG::Point& location) const;
	virtual int getWidth() const;
	virtual int getHeight() const;
	virtual HBitmapIterator createBitmapIterator() const;
	virtual Color getBackgroundColor() const;
private:
	int myWidth;
	int myHeight;
	Color myBackgroundColor;
	PixelMap myPixelMap;

	bool outOfRange(const VG::Point& point) const;
};