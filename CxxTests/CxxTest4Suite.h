#include <cxxtest/TestSuite.h>

class CxxTest4Suite : public CxxTest::TestSuite
{
    char* testString = nullptr;
public:
    void setUp()
    {
        //Run binary with -v option to print this
        TS_TRACE("tearDown called");
        testString = new char[10];
        strcpy(testString,"TESTSTR");
    }
    void tearDown()
    {
        TS_TRACE("tearDown called");
        delete[] testString;
        testString = nullptr;
    }

    void testStringCmp()
    {
        TS_TRACE("testString called");
        TS_TRACE(!strcmp(testString, "TESTSTR"));
        TS_ASSERT(!strcmp(testString, "TESTSTR"));
        TS_ASSERT(true);
        TS_TRACE(testString);
    }
};

