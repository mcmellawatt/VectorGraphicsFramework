#include "WindowsBitmapEncoder.h"
#include "WindowsBitmapHeader.h"
#include "Bitmap.h"
#include "Color.h"
#include "binary_ostream_iterator.h"
#include <stack>

namespace
{
    const std::string WindowsBitmapMimeType("image/x-ms-bmp");
    
    unsigned int numberOfPadBytes(unsigned int widthInPixels)
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

// This constructor is used to create the prototype.
// myBitmapIterator will be unitialized.
// If a client attempts to use an encoder with an
// unitialized iterator, we'll throw an exception.
//
WindowsBitmapEncoder::WindowsBitmapEncoder()
{
}

WindowsBitmapEncoder::WindowsBitmapEncoder(const HBitmapIterator& bitmapIterator) :
myBitmapIterator(bitmapIterator)
{
}

HBitmapEncoder WindowsBitmapEncoder::clone(const HBitmapIterator& bitmapIterator)
{
    return HBitmapEncoder(new WindowsBitmapEncoder(bitmapIterator));
}

void WindowsBitmapEncoder::encodeToStream(std::ostream& destinationStream)
{
    if (! myBitmapIterator.get())
    {
        throw InvalidEncoder();
    }

    WindowsBitmapHeader bitmapHeader;
    bitmapHeader.setBitmapWidth(myBitmapIterator->getBitmapWidth());
    bitmapHeader.setBitmapHeight(myBitmapIterator->getBitmapHeight());

    bitmapHeader.writeFileHeader(destinationStream);
    bitmapHeader.writeInfoHeader(destinationStream);

    std::stack<Bitmap::ScanLine> scanLines;

    while (! myBitmapIterator->isEndOfImage())
    {
        Bitmap::ScanLine scanLine;
        while (! myBitmapIterator->isEndOfScanLine())
        {
            scanLine.push_back(myBitmapIterator->getColor());
            myBitmapIterator->nextPixel();
        }

        scanLines.push(scanLine);
        myBitmapIterator->nextScanLine();
    }

    while (! scanLines.empty())
    {
        Bitmap::ScanLine scanLine = scanLines.top();
        scanLines.pop();
        std::copy(scanLine.begin(), scanLine.end(), binary_ostream_iterator<Color>(destinationStream));
        writePadBytes(destinationStream);
    }
}

std::string WindowsBitmapEncoder::getMimeType() const
{
    return WindowsBitmapMimeType;
}

void WindowsBitmapEncoder::writePadBytes(std::ostream& destinationStream)
{
    Binary::Byte padByte;
    for (int i = 0; i < numberOfPadBytes(myBitmapIterator->getBitmapWidth()); ++i)
    {
        padByte.write(destinationStream);
    }
}