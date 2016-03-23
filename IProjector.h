#pragma once

#include "ICanvas.h"
class IProjector
{
public:
	virtual ~IProjector() {};
	virtual void projectCanvas(const HCanvas& canvas) = 0;
};

typedef Cst::SharedPtr<IProjector> HProjector;