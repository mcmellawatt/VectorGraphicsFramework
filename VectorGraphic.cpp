#include "VectorGraphic.h"
#include "ComputeDimensions.h"
#include "LineIterator.h"

#include <algorithm>

namespace VG
{
    VectorGraphic::VectorGraphic() :
    myShapeStyle(Closed)
    {
    }
    
    VectorGraphic::~VectorGraphic()
    {
    }
    
    bool VectorGraphic::isOpen() const
    {
        return myShapeStyle == Open;
    }
    
    bool VectorGraphic::isClosed() const
    {
        return myShapeStyle == Closed;
    }
    
    void VectorGraphic::openShape()
    {
        myShapeStyle = Open;
    }
    
    void VectorGraphic::closeShape()
    {
        myShapeStyle = Closed;
    }
    
    int VectorGraphic::getWidth() const
    {
        // I'm cheating a bit here by using a function object and the for_each
        // algorithm, which we haven't discussed.
        // I defined ComputeWidth() in ComputeDimensions.h
        
        return std::for_each(myPath.begin(), myPath.end(), ComputeWidth());
        
        // If I were to do the same thing inside this function, it
        // would something like this...
        //
        // int currentMin = INT_MAX;
        // int currentMax = INT_MIN;
        // for (Points::const_iterator i = myPath.begin(); i != myPath.end(); ++i)
        // {
        //     if (i->getX() > currentMax)
        //     {
        //         currentMax = i->getX();
        //     }
        //
        //     if (i->getX() < currentMin)
        //     {
        //         currentMin = i->getX();
        //     }
        // }
        // return currentMax - currentMin;
    }
    
    int VectorGraphic::getHeight() const
    {
        // See my comment above about cheating a bit here...
        return std::for_each(myPath.begin(), myPath.end(), ComputeHeight());
    }
    
    size_t VectorGraphic::getPointCount() const
    {
        return myPath.size();
    }
    
    void VectorGraphic::addPoint(const Point& p)
    {
        myPath.push_back(p);
    }
    
    Point VectorGraphic::getPoint(int index) const
    {
        return myPath.at(index); // throws std::out_of_range if index out of range
    }
    
    void VectorGraphic::removePoint(const Point& p)
    {
        myPath.erase(std::remove(myPath.begin(), myPath.end(), p), myPath.end());
    }
    
    void VectorGraphic::erasePoint(int index)
    {
        if (index >= 0 && static_cast<std::size_t>(index) < myPath.size())
        {
            Points::iterator pos = myPath.begin() + index;
            myPath.erase(pos);
        }
        else
        {
            throw std::out_of_range("index out of range");
        }
    }
    
    bool VectorGraphic::operator==(const VectorGraphic& rhs) const
    {
        return myPath == rhs.myPath;
    }

    bool VectorGraphic::operator!=(const VectorGraphic& rhs) const
    {
        return !operator==(rhs);
    }

    void VectorGraphic::setStroke(const HStroke& stroke)
    {
        myStroke = stroke;
    }

    void VectorGraphic::draw(HCanvas& canvas, const Point& offset) const
    {
        Point previous = myPath[0];
        
        for (Points::size_type i = 1; i < myPath.size(); ++i)
        {
            renderLine(canvas, previous + offset, myPath[i] + offset);
            previous = myPath[i];
        }

        if (myShapeStyle == Closed)
        {
            renderLine(canvas, previous + offset, myPath[0] + offset);
        }
    }

    void VectorGraphic::renderLine(HCanvas& canvas, const Point& p1, const Point& p2) const
    {
        HPen pen = myStroke->createPen(canvas);
        LineIterator line(p1, p2);

        do
        {
            pen->drawPoint(line.getCurrentPoint());
            line.nextPoint();
        }
        while (! line.isEnd());
    }
}
