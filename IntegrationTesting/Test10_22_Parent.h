#ifndef T11_TEST10_22_PARENT_H
#define T11_TEST10_22_PARENT_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test10_22_Parent: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test10_22_Parent);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
};

#endif