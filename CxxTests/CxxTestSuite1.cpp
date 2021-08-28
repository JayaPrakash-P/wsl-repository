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
bool suite_CxxTestSuite1_init = false;
#include "CxxTestSuite1.h"

static CxxTestSuite1 suite_CxxTestSuite1;

static CxxTest::List Tests_CxxTestSuite1 = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_CxxTestSuite1( "CxxTestSuite1.h", 3, "CxxTestSuite1", suite_CxxTestSuite1, Tests_CxxTestSuite1 );

static class TestDescription_suite_CxxTestSuite1_testAddition : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CxxTestSuite1_testAddition() : CxxTest::RealTestDescription( Tests_CxxTestSuite1, suiteDescription_CxxTestSuite1, 6, "testAddition" ) {}
 void runTest() { suite_CxxTestSuite1.testAddition(); }
} testDescription_suite_CxxTestSuite1_testAddition;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
