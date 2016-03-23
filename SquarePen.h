#pragma once

#include "IPen.h"
#include "ICanvas.h"
#include "Color.h"

class SquarePen : public IPen
{
public:
	SquarePen(const HCanvas& canvas, int size, const Color& color);
	virtual	void drawPoint(const VG::Point& point);
private:
	HCanvas	myCanvas;
	int mySize;
	Color myColor;
};