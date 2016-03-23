#include "WindowsBitmapDecoder.h"
#include "BitmapIterator.h"
#include "WindowsBitmapHeader.h"
#include <sstream>

namespace
{
    std::stringstream nullStream;
    const std::string WindowsBitmapMimeType("image/x-ms-bmp");
}

// This constructor is used to create the prototype.
// Initialize mySourceStream to an empty stringstream,
// and set its state to "bad".
// If a client attempts to use a decoder with bad stream,
// we'll throw an exception.
//
WindowsBitmapDecoder::WindowsBitmapDecoder()
    : mySourceStream(nullStream)
{
    mySourceStream.setstate(std::ios::badbit);
}

WindowsBitmapDecoder::WindowsBitmapDecoder(
    std::istream& sourceStream)
    : mySourceStream(sourceStream)
{
}

HBitmapDecoder WindowsBitmapDecoder::clone(
    std::istream& sourceStream)
{
    return HBitmapDecoder(new WindowsBitmapDecoder(sourceStream));
}

HBitmapIterator WindowsBitmapDecoder::createIterator()
{
    if (mySourceStream.bad())
    {
        throw InvalidDecoder();
    }

    WindowsBitmapHeader bitmapHeader;
    bitmapHeader.readFileHeader(mySourceStream);
    bitmapHeader.readInfoHeader(mySourceStream);

    HBitmap bitmap(new Bitmap(
        bitmapHeader.getBitmapWidth(),
        bitmapHeader.getBitmapHeight(),
        mySourceStream));

    return HBitmapIterator(new BitmapIterator(bitmap));
}

std::string WindowsBitmapDecoder::getMimeType() const
{
    return WindowsBitmapMimeType;
}

bool WindowsBitmapDecoder::isSupported(
    const std::string& firstChunk) const
{
    if (firstChunk.size() < 2)
    {
        return false;
    }

    return firstChunk[0] == 'B' && firstChunk[1] == 'M';
}
