#ifndef MTEST_H
#define MTEST_H
#include <cppunit/extensions/HelperMacros.h>

class TestScanner : public CPPUNIT_NS::TestFixture{
  CPPUNIT_TEST_SUITE(TestScanner);
  CPPUNIT_TEST(simpleTest);
  CPPUNIT_TEST_SUITE_END();
public:
  void simpleTest();
};
#endif  // MTEST_H