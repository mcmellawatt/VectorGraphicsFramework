#include "CppUnitLite/TestHarness.h"

#include "CodecLibrary.h"
#include "BrightnessDecorator.h"
#include "ColorInversionDecorator.h"
#include "WindowsBitmapDecoder.h"
#include "WindowsBitmapEncoder.h"
#include "BitmapIterator.h"
#include "SharedPtr.h"
#include <fstream>

const std::string msBmp("image/x-ms-bmp");

namespace
{
    Cst::SharedPtr<CodecLibrary> theCodecLibrary;

    void setUp()
    {
        theCodecLibrary.reset(new CodecLibrary);
        theCodecLibrary->registerEncoder(HBitmapEncoder(new WindowsBitmapEncoder));
        theCodecLibrary->registerDecoder(HBitmapDecoder(new WindowsBitmapDecoder));
    }

    void tearDown()
    {
        theCodecLibrary.reset();
    }
}

TEST(invalidDecoder, CodecLibrary)
{
    HBitmapDecoder decoder(new WindowsBitmapDecoder);

    bool isInvalidDecoder = false;

    try
    {
        decoder->createIterator();
    }
    catch (const InvalidDecoder&)
    {
        isInvalidDecoder = true;
    }

    CHECK(isInvalidDecoder);
}

TEST(invalidEncoder, CodecLibrary)
{
    HBitmapEncoder encoder(new WindowsBitmapEncoder);

    bool isInvalidEncoder = false;

    try
    {
        std::ostringstream os(std::ios::binary);
        encoder->encodeToStream(os);
    }
    catch (const InvalidEncoder&)
    {
        isInvalidEncoder = true;
    }

    CHECK(isInvalidEncoder);
}

//TEST(createEncoderViaMimeType, CodecLibrary)
//{
//    setUp();
//    
//    std::stringstream nullStream;
//    HBitmap nullBitmap(new Bitmap(0, 0, nullStream));
//    HBitmapIterator iterator(new BitmapIterator(nullBitmap));
//    HBitmapEncoder encoder = theCodecLibrary->createEncoder(msBmp, iterator);
//
//    CHECK(dynamic_cast<WindowsBitmapEncoder*>(encoder.get()));
//
//    tearDown();
//}

TEST(createDecoderViaMimeType, CodecLibrary)
{
    setUp();

    std::stringstream ss;
    HBitmapDecoder decoder = theCodecLibrary->createDecoder(msBmp, ss);

    CHECK(dynamic_cast<WindowsBitmapDecoder*>(decoder.get()));

    tearDown();
}

TEST(createDecoderAutoDetermine, CodecLibrary)
{
    setUp();

    std::ifstream inFile("basic.bmp", std::ios::binary);
    CHECK_EQUAL(0, !inFile);
    HBitmapDecoder decoder = theCodecLibrary->createDecoder(inFile);

    CHECK(decoder.get());
    CHECK(dynamic_cast<WindowsBitmapDecoder*>(decoder.get()));

    tearDown();
}

TEST(windowsBitmapDecodeEncode, CodecLibrary)
{
    setUp();

    std::ifstream inFile("basic.bmp", std::ios::binary);
    CHECK_EQUAL(0, !inFile);
    
    HBitmapDecoder decoder = theCodecLibrary->createDecoder(inFile);
    HBitmapIterator iterator = decoder->createIterator();
    
    CHECK(iterator.get());
    CHECK_EQUAL(100, iterator->getBitmapHeight());
    CHECK_EQUAL(100, iterator->getBitmapWidth());

    HBitmapEncoder encoder = theCodecLibrary->createEncoder(msBmp, iterator);

    std::ofstream outFile("output_basicCopy.bmp", std::ios::binary);
    encoder->encodeToStream(outFile);
    // TODO: file compare input/output

    tearDown();
}

TEST(brightnessDecoratorIterator, CodecLibrary)
{
    setUp();

    std::ifstream inFile("basic.bmp", std::ios::binary);
    CHECK_EQUAL(0, !inFile);
    
    HBitmapDecoder decoder = theCodecLibrary->createDecoder(inFile);
    HBitmapIterator iterator = decoder->createIterator();
    
    CHECK(iterator.get());
    CHECK_EQUAL(100, iterator->getBitmapHeight());
    CHECK_EQUAL(100, iterator->getBitmapWidth());

    HBitmapIterator brightnessIterator(new BrightnessDecorator(iterator, 80));
    HBitmapEncoder encoder = theCodecLibrary->createEncoder(msBmp, brightnessIterator);

    std::ofstream outFile("output_basicBrightnessAdjusted.bmp", std::ios::binary);
    encoder->encodeToStream(outFile);
    // TODO: file compare input/output

    tearDown();
}

TEST(colorInvertDecoratorIterator, CodecLibrary)
{
    setUp();

    std::ifstream inFile("basic.bmp", std::ios::binary);
    CHECK_EQUAL(0, !inFile);
    
    HBitmapDecoder decoder = theCodecLibrary->createDecoder(inFile);
    HBitmapIterator iterator = decoder->createIterator();
    
    CHECK(iterator.get());
    CHECK_EQUAL(100, iterator->getBitmapHeight());
    CHECK_EQUAL(100, iterator->getBitmapWidth());

    HBitmapIterator colorInvertIterator(new ColorInversionDecorator(iterator));
    HBitmapEncoder encoder = theCodecLibrary->createEncoder(msBmp, colorInvertIterator);

    std::ofstream outFile("output_basicColorInvert.bmp", std::ios::binary);
    encoder->encodeToStream(outFile);
    // TODO: file compare input/output

    tearDown();
}

TEST(doubleDecorator, CodecLibrary)
{
    setUp();

    std::ifstream inFile("basic.bmp", std::ios::binary);
    CHECK_EQUAL(0, !inFile);
    
    HBitmapDecoder decoder = theCodecLibrary->createDecoder(inFile);
    HBitmapIterator iterator = decoder->createIterator();
    
    CHECK(iterator.get());
    CHECK_EQUAL(100, iterator->getBitmapHeight());
    CHECK_EQUAL(100, iterator->getBitmapWidth());

    HBitmapIterator colorInvertIterator(new ColorInversionDecorator(iterator));
    HBitmapIterator darkenColorInvertIterator(new BrightnessDecorator(colorInvertIterator, -50));

    HBitmapEncoder encoder = theCodecLibrary->createEncoder(msBmp, darkenColorInvertIterator);
        
    std::ofstream outFile("output_darkInverted.bmp", std::ios::binary);
    encoder->encodeToStream(outFile);
    // TODO: file compare input/output

    tearDown();
}
