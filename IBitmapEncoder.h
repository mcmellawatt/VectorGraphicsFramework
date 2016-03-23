#pragma once

#include "IBitmapIterator.h"
#include "SharedPtr.h"
#include <string>

class IBitmapEncoder;

typedef Cst::SharedPtr<IBitmapEncoder> HBitmapEncoder;

class IBitmapEncoder
{
public:
    virtual ~IBitmapEncoder() { }

    virtual HBitmapEncoder clone(
        const HBitmapIterator& bitmapIterator) = 0;

    virtual void encodeToStream(
        std::ostream& os) = 0;

    virtual std::string getMimeType() const = 0;
};

class InvalidEncoder : public std::runtime_error
{
public:
    InvalidEncoder() : std::runtime_error("Invalid encoder") { }
};
