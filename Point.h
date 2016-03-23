#pragma once

#include <iosfwd>

namespace VG
{
	class Point
	{
	public:
		Point(int x = 0, int y = 0);
        
		int getX() const;
		int getY() const;
        
		VG::Point Point::operator+(const VG::Point& rhs) const;
	private:
		int myX;
		int myY;
	};
    
    bool operator==(const Point& lhs, const Point& rhs);
    bool operator!=(const Point& lhs, const Point& rhs);

    std::ostream& operator<<(std::ostream& os, const Point& p);

	struct PointCompare
	{
	   bool operator() (const Point& lhs, const Point& rhs)
	   {
		   if (lhs.getX() < rhs.getX())
			   return true;
		   else if (lhs.getX() > rhs.getX())
			   return false;
		   else if (lhs.getY() < rhs.getY())
			   return true;
		   else
			   return false;
	   }
	};
}
