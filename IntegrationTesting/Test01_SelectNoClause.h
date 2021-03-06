#ifndef T11_TEST01_SELECT_NO_CLAUSE_H
#define T11_TEST01_SELECT_NO_CLAUSE_H

#include <string>
#include <cppunit/extensions/HelperMacros.h>

class Test01_SelectNoClause: public CPPUNIT_NS::TestFixture {
CPPUNIT_TEST_SUITE(Test01_SelectNoClause);
CPPUNIT_TEST(test_select_one_syn);
CPPUNIT_TEST(test_select_one_syn_attr);
CPPUNIT_TEST(test_select_two_same_syn);
CPPUNIT_TEST(test_select_syn_syn_attr);
CPPUNIT_TEST(test_select_X_Y_Xattr);
CPPUNIT_TEST(test_select_boolean);
CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
private:
    std::string SELECT_ONE_SIMPLEPROG;
    void test_select_one_syn();
    void test_select_one_syn_attr();
    /*
     * Select same synonym 2 times.
     * eg. assign a; Select <a,a>
     */
    void test_select_two_same_syn();
    /*
     * Select synonym and its attribute.
     * eg. stmt s; Select <s,s.stmt#>
     */
    void test_select_syn_syn_attr();
    /*
     * Select a synonym (X), another synonym (Y), and X.attr
     * eg. assign a; variable v; Select <v, a, v.varName>
     */
    void test_select_X_Y_Xattr();
    void test_select_boolean();
};

#endif