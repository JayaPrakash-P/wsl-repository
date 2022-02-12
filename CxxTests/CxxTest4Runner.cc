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
bool suite_CxxTest4Suite_init = false;
#include "CxxTest4Suite.h"

static CxxTest4Suite suite_CxxTest4Suite;

static CxxTest::List Tests_CxxTest4Suite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_CxxTest4Suite( "CxxTest4Suite.h", 3, "CxxTest4Suite", suite_CxxTest4Suite, Tests_CxxTest4Suite );

static class TestDescription_suite_CxxTest4Suite_testStringCmp : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_CxxTest4Suite_testStringCmp() : CxxTest::RealTestDescription( Tests_CxxTest4Suite, suiteDescription_CxxTest4Suite, 21, "testStringCmp" ) {}
 void runTest() { suite_CxxTest4Suite.testStringCmp(); }
} testDescription_suite_CxxTest4Suite_testStringCmp;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
