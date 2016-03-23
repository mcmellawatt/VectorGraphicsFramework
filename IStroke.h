#pragma once

#include "IPen.h"
#include "ICanvas.h"

class IStroke;

typedef Cst::SharedPtr<IStroke> HStroke;

class IStroke
{
public:
	virtual ~IStroke() {}
	virtual HPen createPen(const HCanvas& canvas) = 0;
};