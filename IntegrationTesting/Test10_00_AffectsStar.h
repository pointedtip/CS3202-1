#ifndef T11_TEST10_00_AFFECTS_STAR_H
#define T11_TEST10_00_AFFECTS_STAR_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_00_AffectsStar: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_00_AffectsStar);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_affects_star_stmt_00();
    std::string AFFECTS_STAR_00_PROG;
};

#endif