#pragma once

#include "IBitmapIterator.h"
#include "SharedPtr.h"
#include <iostream>
#include <string>

class IBitmapDecoder;

typedef Cst::SharedPtr<IBitmapDecoder> HBitmapDecoder;

class IBitmapDecoder
{
public:
    virtual ~IBitmapDecoder() { }

    virtual HBitmapDecoder clone(
        std::istream& sourceStream) = 0;

    virtual HBitmapIterator createIterator() = 0;

    virtual std::string getMimeType() const = 0;

    virtual bool isSupported(
        const std::string& firstChunk) const = 0;
};

class InvalidDecoder : public std::runtime_error
{
public:
    InvalidDecoder() : std::runtime_error("Invalid decoder") { }
};
