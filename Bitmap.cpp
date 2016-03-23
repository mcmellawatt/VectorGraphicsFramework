#include "Bitmap.h"

namespace
{
    unsigned int numberOfPadBytes(Binary::DoubleWord widthInPixels)
    {
        unsigned int pad = 0;
        unsigned int remainder = (widthInPixels * 3) % 4;
        
        if (remainder > 0)
        {
            pad = 4 - remainder;
        }

        return pad;
    }
}

Bitmap::Bitmap(Binary::DoubleWord width,
               Binary::DoubleWord height,
               std::istream& sourceStream) :
myWidth(width),
myHeight(height),
myNumberOfPadBytes(numberOfPadBytes(width))
{
    read(sourceStream);
}

Binary::DoubleWord Bitmap::getWidth() const
{
    return myWidth;
}

Binary::DoubleWord Bitmap::getHeight() const
{
    return myHeight;
}

unsigned int Bitmap::getNumberOfPadBytes() const
{
    return myNumberOfPadBytes;
}

Bitmap::ScanLineIterator Bitmap::begin()
{
    return myScanLines.begin();
}

Bitmap::ScanLineIterator Bitmap::end()
{
    return myScanLines.end();
}

void Bitmap::read(std::istream& sourceStream)
{
    myScanLines.clear();
    
    for (int row = 0; row < myHeight; ++row)
    {
        ScanLine scanLine;

        for (int column = 0; column < myWidth; ++column)
        {
            scanLine.push_back(Color::read(sourceStream));
        }

        // Read pad bytes
        for (unsigned int pad = 0; pad < myNumberOfPadBytes; ++pad)
        {
            Binary::Byte::read(sourceStream);
        }

        myScanLines.push_back(scanLine);
    }
}

void Bitmap::write(std::ostream& destinationStream) const
{
    for (Bitmap::ScanLineCollection::const_iterator scanLine = myScanLines.begin();
         scanLine != myScanLines.end();
         ++scanLine)
    {
        for (Bitmap::ScanLine::const_iterator color = scanLine->begin();
             color != scanLine->end();
             ++color)
        {
            color->write(destinationStream);
        }

        // Write pad bytes
        for (unsigned int pad = 0; pad < myNumberOfPadBytes; ++pad)
        {
            Binary::Byte(0).write(destinationStream);
        }
    }
}