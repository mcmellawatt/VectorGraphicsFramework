#pragma once

#include "IBitmapEncoder.h"

class WindowsBitmapEncoder: public IBitmapEncoder
{
public:
    WindowsBitmapEncoder();
    WindowsBitmapEncoder(const HBitmapIterator& bitmapIterator);

    virtual HBitmapEncoder clone(const HBitmapIterator& bitmapIterator);

    virtual void encodeToStream(std::ostream& destinationStream);

    virtual std::string getMimeType() const;

private:
    HBitmapIterator myBitmapIterator;

    void writePadBytes(std::ostream& destinationStream);
};
