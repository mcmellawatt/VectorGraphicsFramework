#include "CppUnitLite/TestHarness.h"
#include "DoubleWord.h"
#include "Byte.h"
#include "Word.h"
#include <sstream>

TEST(readByte, Byte)
{
    std::stringstream ss("abc");
    
    Binary::Byte b = Binary::Byte::read(ss);
    CHECK_EQUAL('a', b);
    
    b = Binary::Byte::read(ss);
    CHECK_EQUAL('b', b);
    
    b = Binary::Byte::read(ss);
    CHECK_EQUAL('c', b);
}

TEST(writeByte, Byte)
{
    Binary::Byte b('x');
    
    std::stringstream ss;
    b.write(ss);
    
    CHECK_EQUAL("x", ss.str());
}

TEST(readWordLittleEndian, Binary)
{
    unsigned char carray[] = { 0xb1, 0xb2, 0 };
    std::stringstream ss(reinterpret_cast<char*>(carray));
    
    Binary::Word expected(0xb2b1);
    Binary::Word actual = Binary::Word::readLittleEndian(ss);
    
    CHECK_EQUAL(expected, actual);
}

TEST(readWordBigEndian, Binary)
{
    unsigned char carray[] = { 0xb1, 0xb2, 0 };
    std::stringstream ss(reinterpret_cast<char*>(carray));
    
    Binary::Word expected(0xb1b2);
    Binary::Word actual = Binary::Word::readBigEndian(ss);
    
    CHECK_EQUAL(expected, actual);
}

TEST(readDoubleWordLittleEndian, Binary)
{
    unsigned char carray[] = { 0xb1, 0xb2, 0xb3, 0xb4, 0 };
    std::stringstream ss(reinterpret_cast<char*>(carray));
    
    Binary::DoubleWord expected(0xb4b3b2b1);
    Binary::DoubleWord actual = Binary::DoubleWord::readLittleEndian(ss);
    
    CHECK_EQUAL(expected, actual);
}

TEST(readDoubleWordBigEndian, Binary)
{
    unsigned char carray[] = { 0xb1, 0xb2, 0xb3, 0xb4, 0 };
    std::stringstream ss(reinterpret_cast<char*>(carray));
    
    Binary::DoubleWord expected(0xb1b2b3b4);
    Binary::DoubleWord actual = Binary::DoubleWord::readBigEndian(ss);
    
    CHECK_EQUAL(expected, actual);
}