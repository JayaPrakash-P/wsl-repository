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
bool suite_CxxTestSuite5_init = false;
#include "CxxTestSuite3.h"

static CxxTestSuite5 suite_CxxTestSuite5;

static CxxTest::List Tests_CxxTestSuite5 = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_CxxTestSuite5( "CxxTestSuite3.h", 4, "CxxTestSuite5", suite_CxxTestSuite5, Tests_CxxTestSuite5 );

static class TestDescription_suite_CxxTestSuite5_test_strcpy : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CxxTestSuite5_test_strcpy() : CxxTest::RealTestDescription( Tests_CxxTestSuite5, suiteDescription_CxxTestSuite5, 20, "test_strcpy" ) {}
 void runTest() { suite_CxxTestSuite5.test_strcpy(); }
} testDescription_suite_CxxTestSuite5_test_strcpy;

static class TestDescription_suite_CxxTestSuite5_test_memcpy : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CxxTestSuite5_test_memcpy() : CxxTest::RealTestDescription( Tests_CxxTestSuite5, suiteDescription_CxxTestSuite5, 27, "test_memcpy" ) {}
 void runTest() { suite_CxxTestSuite5.test_memcpy(); }
} testDescription_suite_CxxTestSuite5_test_memcpy;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
