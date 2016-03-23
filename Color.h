#pragma once

#include "Byte.h"

class Color
{
public:
    Color(const Binary::Byte& red,
          const Binary::Byte& green,
          const Binary::Byte& blue);
    
    static Color read(std::istream& sourceStream);
    void write(std::ostream& destinationStream) const;

    Binary::Byte getRed() const;
    Binary::Byte getGreen() const;
    Binary::Byte getBlue() const;

private:
    Binary::Byte myRed;
    Binary::Byte myGreen;
    Binary::Byte myBlue;
};

bool operator== (const Color &color1, const Color &color2);
std::ostream& operator<<(std::ostream& os, const Color& color);
