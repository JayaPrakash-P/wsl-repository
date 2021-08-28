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
bool suite_CxxTestSuite2_init = false;
#include "CxxTestSuite2.h"

static CxxTestSuite2 suite_CxxTestSuite2;

static CxxTest::List Tests_CxxTestSuite2 = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_CxxTestSuite2( "CxxTestSuite2.h", 1, "CxxTestSuite2", suite_CxxTestSuite2, Tests_CxxTestSuite2 );

static class TestDescription_suite_CxxTestSuite2_testAddition : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CxxTestSuite2_testAddition() : CxxTest::RealTestDescription( Tests_CxxTestSuite2, suiteDescription_CxxTestSuite2, 4, "testAddition" ) {}
 void runTest() { suite_CxxTestSuite2.testAddition(); }
} testDescription_suite_CxxTestSuite2_testAddition;

static class TestDescription_suite_CxxTestSuite2_testMultiplication : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CxxTestSuite2_testMultiplication() : CxxTest::RealTestDescription( Tests_CxxTestSuite2, suiteDescription_CxxTestSuite2, 10, "testMultiplication" ) {}
 void runTest() { suite_CxxTestSuite2.testMultiplication(); }
} testDescription_suite_CxxTestSuite2_testMultiplication;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
