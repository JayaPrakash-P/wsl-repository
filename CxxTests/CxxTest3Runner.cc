/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_CxxTestSuite333_init = false;
#include "CxxTest3Suite.h"

static CxxTestSuite333 suite_CxxTestSuite333;

static CxxTest::List Tests_CxxTestSuite333 = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_CxxTestSuite333( "CxxTest3Suite.h", 4, "CxxTestSuite333", suite_CxxTestSuite333, Tests_CxxTestSuite333 );

static class TestDescription_suite_CxxTestSuite333_test_strcpy : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CxxTestSuite333_test_strcpy() : CxxTest::RealTestDescription( Tests_CxxTestSuite333, suiteDescription_CxxTestSuite333, 20, "test_strcpy" ) {}
 void runTest() { suite_CxxTestSuite333.test_strcpy(); }
} testDescription_suite_CxxTestSuite333_test_strcpy;

static class TestDescription_suite_CxxTestSuite333_test_memcpy : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CxxTestSuite333_test_memcpy() : CxxTest::RealTestDescription( Tests_CxxTestSuite333, suiteDescription_CxxTestSuite333, 27, "test_memcpy" ) {}
 void runTest() { suite_CxxTestSuite333.test_memcpy(); }
} testDescription_suite_CxxTestSuite333_test_memcpy;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
