#ifndef T11_TEST_PKB_H
#define T11_TEST_PKB_H

#include <cppunit/extensions/HelperMacros.h>
#include <set>


using std::set;


class TestPKB: public CPPUNIT_NS::TestFixture {

CPPUNIT_TEST_SUITE(TestPKB);
CPPUNIT_TEST(test_one);
//CPPUNIT_TEST(test_two);
//CPPUNIT_TEST(test_three);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();

private:
    void test_one();
    void test_two();
    void test_three();


};

#endif