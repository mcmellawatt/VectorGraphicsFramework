#pragma once

#include "SharedPtr.h"
#include "BitmapIterator.h"
#include "Point.h"

class ICanvas
{
public:
	virtual ~ICanvas() {};

	virtual void setPixelColor(const VG::Point& location, const Color& color) = 0;
	virtual Color getPixelColor(const VG::Point& location) const = 0;
	virtual int getWidth() const = 0;
	virtual int getHeight() const = 0;
	virtual HBitmapIterator createBitmapIterator() const = 0;
	virtual Color getBackgroundColor() const = 0;
};

typedef Cst::SharedPtr<ICanvas> HCanvas;

class PixelLocationOutOfRange : public std::runtime_error
{
public:
	PixelLocationOutOfRange() : std::runtime_error("Pixel location out of range") {}
};
