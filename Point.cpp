#include "Point.h"
#include <iostream>

namespace VG
{
	Point::Point(int x, int y) :
    myX(x),
    myY(y)
	{
	}
    
	int Point::getX() const
	{
		return myX;
	}
    
	int Point::getY() const
	{
		return myY;
	}
    
	std::ostream& operator<<(std::ostream& os, const Point& p)
	{
		os << "(" << p.getX() << ", " << p.getY() << ")";
		return os;
	}
    
    bool operator==(const Point& lhs, const Point& rhs)
	{
        return rhs.getX() == lhs.getX() && rhs.getY() == lhs.getY();
	}
    
	bool operator!=(const Point& lhs, const Point& rhs)
	{
		return !operator==(lhs, rhs);
	}

	VG::Point Point::operator+(const VG::Point& rhs) const
	{
		return VG::Point((this->getX()+rhs.getX()),(this->getY()+rhs.getY()));
	}

}
