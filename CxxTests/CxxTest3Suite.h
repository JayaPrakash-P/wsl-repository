#include <cxxtest/TestSuite.h>
#include <string.h>

class CxxTestSuite333 : public CxxTest::TestSuite
{
    char *_buffer;

public:

    void setUp()
    {
        _buffer = new char[1024];
    }

    void tearDown()
    {
        delete [] _buffer;
    }

    void test_strcpy()
    {
        strcpy(_buffer, "Hello, world!");
        TS_ASSERT_EQUALS(_buffer[0], 'H');
        TS_ASSERT_EQUALS(_buffer[1], 'e');
        TS_ASSERT_EQUALS(_buffer[2], 'l');
        TS_ASSERT_EQUALS(_buffer[3], 'l');
        TS_ASSERT_EQUALS(_buffer[4], 'o');
        TS_ASSERT_EQUALS(_buffer[5], ',');
        TS_ASSERT_EQUALS(_buffer[6], ' ');
        TS_ASSERT_EQUALS(_buffer[7], 'w');
        TS_ASSERT_EQUALS(_buffer[8], 'o');
        TS_ASSERT_EQUALS(_buffer[9], 'r');
        TS_ASSERT_EQUALS(_buffer[10], 'l');
        TS_ASSERT_EQUALS(_buffer[11], 'd');
        TS_ASSERT_EQUALS(_buffer[12], '!');
        TS_ASSERT_EQUALS(_buffer[13], 0);
    }

    void test_memcpy()
    {
        memcpy(_buffer, "Hello, world!", 1024);
        TS_TRACE(strlen(_buffer));
        TS_ASSERT_EQUALS(_buffer[0], 'H');
        TS_ASSERT_EQUALS(_buffer[1], 'e');
        TS_ASSERT_EQUALS(_buffer[2], 'l');
        TS_ASSERT_EQUALS(_buffer[3], 'l');
        TS_ASSERT_EQUALS(_buffer[4], 'o');
        TS_ASSERT_EQUALS(_buffer[5], ',');
        TS_ASSERT_EQUALS(_buffer[6], ' ');
        TS_ASSERT_EQUALS(_buffer[7], 'w');
        TS_ASSERT_EQUALS(_buffer[8], 'o');
        TS_ASSERT_EQUALS(_buffer[9], 'r');
        TS_ASSERT_EQUALS(_buffer[10], 'l');
        TS_ASSERT_EQUALS(_buffer[11], 'd');
        TS_ASSERT_EQUALS(_buffer[12], '!');
        TS_ASSERT_EQUALS(_buffer[13], 0);
        TS_TRACE(strlen(_buffer));
    }
};
