#pragma once

#include "Point.h"
#include "SharedPtr.h"
#include <vector>
#include "IStroke.h"

namespace VG
{
    typedef std::vector<Point> Points;

    class VectorGraphic
    {
	public:
		VectorGraphic();
		~VectorGraphic();
        
		void addPoint(const Point& p);
		void removePoint(const Point& p);
		void erasePoint(int index);
        
		void openShape();
		void closeShape();
        
		bool isOpen() const;
		bool isClosed() const;
        
		int getWidth() const;
		int getHeight() const;
        
		size_t getPointCount() const;
		Point getPoint(int index) const;
        
		bool operator==(const VectorGraphic& rhs) const;
		bool operator!=(const VectorGraphic& rhs) const;
        
		void setStroke(const HStroke& stroke);

		void draw(HCanvas& canvas, const Point& offset) const;
	private:
		Points myPath;
        HStroke myStroke;

		enum ShapeStyle
		{
			Open,
			Closed
		} myShapeStyle;

		void renderLine(HCanvas& canvas, const Point& p1, const Point& p2) const;
    };
    
    typedef Cst::SharedPtr<VectorGraphic> HVectorGraphic;
    
}
