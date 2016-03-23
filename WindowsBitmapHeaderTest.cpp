#include "CppUnitLite/TestHarness.h"
#include "WindowsBitmapHeader.h"
#include <fstream>

TEST(InfoHeaderTest, WindowBitmapHeader)
{
    std::ifstream bitmapStream("basic.bmp", std::ios::binary);
    CHECK(bitmapStream.is_open());
    WindowsBitmapHeader bitmapHeader;
    bitmapHeader.readFileHeader(bitmapStream);
    bitmapHeader.readInfoHeader(bitmapStream);

    CHECK_EQUAL(100, bitmapHeader.getBitmapHeight());
    CHECK_EQUAL(100, bitmapHeader.getBitmapWidth());
}

// --- Repeat similar tests for 101x101 bitmap

TEST(InfoHeaderTest_101, WindowBitmapHeader)
{
    std::ifstream bitmapStream("basic_101.bmp", std::ios::binary);
    CHECK(bitmapStream.is_open());
    WindowsBitmapHeader bitmapHeader;
    bitmapHeader.readFileHeader(bitmapStream);
    bitmapHeader.readInfoHeader(bitmapStream);
    
    CHECK_EQUAL(101, bitmapHeader.getBitmapHeight());
    CHECK_EQUAL(101, bitmapHeader.getBitmapWidth());
}
