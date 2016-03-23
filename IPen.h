#pragma once

#include "Point.h"
#include "SharedPtr.h"

class IPen;

typedef Cst::SharedPtr<IPen> HPen;

class IPen
{
public:
	virtual ~IPen()	 { };
	virtual void drawPoint(const VG::Point& p) = 0;
};

