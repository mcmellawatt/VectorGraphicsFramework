#pragma once

#include "IBitmapDecoder.h"
#include "IBitmapEncoder.h"
#include <list>
#include <istream>
#include <string>

class CodecLibrary
{
public:
    void registerEncoder(const HBitmapEncoder& encoder);
    void registerDecoder(const HBitmapDecoder& decoder);

    // auto determination version of createDecoder
    HBitmapDecoder createDecoder(
        std::istream& sourceStream);

    // mime type version of createDecoder
    HBitmapDecoder createDecoder(
        const std::string& mimeType,
        std::istream& sourceStream);

    HBitmapEncoder createEncoder(
        const std::string& mimeType,
        const HBitmapIterator& bitmapIterator);

private:
    std::list<HBitmapEncoder> myEncoders;
    std::list<HBitmapDecoder> myDecoders;

    typedef std::list<HBitmapEncoder>::iterator EncoderIterator;
    typedef std::list<HBitmapDecoder>::iterator DecoderIterator;
};
