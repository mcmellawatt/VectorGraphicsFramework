#include "Word.h"
#include "Byte.h"
#include <iostream>

namespace Binary
{

    Word::Word(uint16_t value)
    {
        myValue = value;
    }

    Word::operator uint16_t() const
    {
        return myValue;
    }

    Word& Word::operator=(const Word& rhs)
    {
        myValue = rhs.myValue;
        return *this;
    }

    Word& Word::operator=(uint16_t rhs)
    {
        myValue = rhs;
        return *this;
    }

    void Word::writeLittleEndian(std::ostream& destinationStream) const
    {
#ifdef Little_Endian_
        writeNativeOrder(destinationStream);
#else
        writeSwappedOrder(destinationStream);
#endif
    }

    void Word::writeBigEndian(std::ostream& destinationStream) const
    {
#ifdef Little_Endian_
        writeSwappedOrder(destinationStream);
#else
        writeNativeOrder(destinationStream);
#endif
    }

    Word Word::readBigEndian(std::istream& sourceStream)
    {
#ifdef Little_Endian_
        return readSwappedOrder(sourceStream);
#else
        return readNativeOrder(sourceStream);
#endif
    }

    Word Word::readLittleEndian(std::istream& sourceStream)
    {
#ifdef Little_Endian_
        return readNativeOrder(sourceStream);
#else
        return readSwappedOrder(sourceStream);
#endif
    }

    Word Word::readNativeOrder(std::istream& sourceStream)
    {
        Word word;
        Byte* bytes = reinterpret_cast<Byte*>(&word);
        
        bytes[0] = sourceStream.get();
        bytes[1] = sourceStream.get();
        
        return word;
    }

    Word Word::readSwappedOrder(std::istream& sourceStream)
    {
        Word word;
        Byte* bytes = reinterpret_cast<Byte*>(&word);
        
        bytes[1] = sourceStream.get();
        bytes[0] = sourceStream.get();
        
        return word;
    }

    void Word::writeNativeOrder(std::ostream& destinationStream) const
    {
        const Byte* bytes = reinterpret_cast<const Byte*>(&myValue);
        
        destinationStream.put(bytes[0]);
        destinationStream.put(bytes[1]);
    }

    void Word::writeSwappedOrder(std::ostream& destinationStream) const
    {
        const Byte* bytes = reinterpret_cast<const Byte*>(&myValue);
        
        destinationStream.put(bytes[1]);
        destinationStream.put(bytes[0]);
    }
}
