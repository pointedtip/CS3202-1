#ifndef TEST_20_SELECT_SYN_SYN_RELREF_H
#define TEST_20_SELECT_SYN_SYN_RELREF_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test_20_SynSyn_RelRef: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test_20_SynSyn_RelRef);
CPPUNIT_TEST(test_uses_modifies_same_variable);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    void test_uses_modifies_same_variable();
};

#endif