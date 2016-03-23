#include "CppUnitLite/TestHarness.h"
#include "VerifyEquality.h"
#include "Word.h"
#include <iostream>

TEST(verifyEquality, Word)
{
    const unsigned char input[] = { 0xAB, 0xCD };
    std::stringstream ss;
    ss.write(reinterpret_cast<const char*>(input), 2);
    ss.seekg(0, std::ios::beg);

    Binary::Word actual = Binary::Word::readLittleEndian(ss);
    Binary::Word notReallyExpected(0xABCD);

    try
    {
        verifyEquality(notReallyExpected, actual, "notReallyExpected");
        CHECK(false);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        CHECK(true);
    }
}