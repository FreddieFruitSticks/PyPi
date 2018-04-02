#include <cppunit/config/SourcePrefix.h>
#include <TestScanner.h>

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(TestScanner);

// Some code to be tested.
void TestScanner::simpleTest() {
  CPPUNIT_ASSERT_EQUAL(1, 2);
}