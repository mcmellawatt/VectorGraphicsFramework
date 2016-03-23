#pragma once

#include "Color.h"
#include "DoubleWord.h"
#include "SharedPtr.h"
#include <list>

class Bitmap
{
public:
    typedef std::list<Color> ScanLine;
    typedef ScanLine::iterator ColorIterator;

private:
    typedef std::list<ScanLine> ScanLineCollection;

public:
    typedef ScanLineCollection::iterator ScanLineIterator;

    Bitmap(Binary::DoubleWord width,
           Binary::DoubleWord height,
           std::istream& sourceStream);

    ScanLineIterator begin();
    ScanLineIterator end();

    Binary::DoubleWord getWidth() const;
    Binary::DoubleWord getHeight() const;
    unsigned int getNumberOfPadBytes() const;

    void read(std::istream& sourceStream);
    void write(std::ostream& destinationStream) const;

private:
    Binary::DoubleWord myWidth;
    Binary::DoubleWord myHeight;
    unsigned int myNumberOfPadBytes;

    ScanLineCollection myScanLines;
};

typedef Cst::SharedPtr<Bitmap> HBitmap;
