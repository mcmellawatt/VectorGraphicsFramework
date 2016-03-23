#include "CodecLibrary.h"

namespace
{
    const int ChunkSize(100);
}

void CodecLibrary::registerEncoder(const HBitmapEncoder& encoder)
{
    myEncoders.push_back(encoder);
}

void CodecLibrary::registerDecoder(const HBitmapDecoder& decoder)
{
    myDecoders.push_back(decoder);
}

// auto determination version of createDecoder
HBitmapDecoder CodecLibrary::createDecoder(std::istream& sourceStream)
{
    // get first chunk to use for type determination
    char firstChunk[ChunkSize];
    sourceStream.get(firstChunk, ChunkSize);

    // reposition stream back to beginning
    sourceStream.clear();
    sourceStream.seekg(sourceStream.beg);

    for (DecoderIterator decoder = myDecoders.begin();
        decoder != myDecoders.end();
        ++decoder)
    {
        if ((*decoder)->isSupported(firstChunk))
        {
            return (*decoder)->clone(sourceStream);
        }
    }
    return HBitmapDecoder();
}

// mime type version of createDecoder
HBitmapDecoder CodecLibrary::createDecoder(const std::string& mimeType,
                                           std::istream& sourceStream)
{
    for (DecoderIterator decoder = myDecoders.begin();
        decoder != myDecoders.end();
        ++decoder)
    {
        if ((*decoder)->getMimeType() == mimeType)
        {
            return (*decoder)->clone(sourceStream);
        }
    }
    
    // If we didn't find an appropriate encoder we return a "null" one
    return HBitmapDecoder();
}

HBitmapEncoder CodecLibrary::createEncoder(const std::string& mimeType,
                                           const HBitmapIterator& bitmapIterator)
{
    for (EncoderIterator encoder = myEncoders.begin();
         encoder != myEncoders.end();
         ++encoder)
    {
        if ((*encoder)->getMimeType() == mimeType)
        {
            return (*encoder)->clone(bitmapIterator);
        }
    }
    
    // If we didn't find an appropriate encoder we return a "null" one
    return HBitmapEncoder();
}
