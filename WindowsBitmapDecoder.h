#pragma once

#include "IBitmapDecoder.h"

class WindowsBitmapDecoder: public IBitmapDecoder
{
public:
    WindowsBitmapDecoder();

    WindowsBitmapDecoder(
        std::istream& sourceStream);

    virtual HBitmapDecoder clone(
        std::istream& sourceStream);

    virtual HBitmapIterator createIterator();

    virtual std::string getMimeType() const;

    virtual bool isSupported(
        const std::string& firstChunk) const;

public:
    std::istream& mySourceStream;
};
