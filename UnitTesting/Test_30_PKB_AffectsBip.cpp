#include <cstdarg>
#include <string>
#include <map>
#include <memory>
#include "Test_30_PKB_AffectsBip.h"
#include "../SPA/Parser.h"
#include "../SPA/PKB.h"
#include "../SPA/SetWrapper.h"

using std::auto_ptr;
using std::string;
using std::map;

void Test_30_PKB_AffectsBip::setUp(){}
void Test_30_PKB_AffectsBip::tearDown(){}
CPPUNIT_TEST_SUITE_REGISTRATION(Test_30_PKB_AffectsBip);

void Test_30_PKB_AffectsBip::test_AffectsBip()
{
        const string& simpleProg =
            "procedure left {\
                dd = 1 + cc;\
                bb = 2 + aa;\
            }\
            procedure one {\
                call two;\
            }\
            procedure two{\
                cc = 4 +bb;\
            }\
            procedure main{\
                while i5 {\
                    if i6 then {\
                        call left;\
                    } else {\
                        call right; }\
                    a = 9 + b;\
                    b = 10 + a;\
                }\
            }\
            procedure right{\
                ee = 11 + dd;\
                call one;\
                aa = 13;\
            }";

    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());

    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(9,10));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(10,9));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(13,2));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(2,4));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(4,1));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(1,11));

}

void Test_30_PKB_AffectsBip::test_AffectsBip_multiproc()
{
        const string& simpleProg =
            "procedure one{\
                a = 1;\
                call mid;\
                aa = 3 + c;\
            }\
            procedure two {\
                b = 4;\
                call mid;\
                bb = 6 + a;\
            }\
            procedure three{\
                c = 7;\
                call mid;\
                cc = 9 + b;\
            }\
            procedure mid{\
                d = 10;\
            }\
            procedure four{\
                d = 11;\
                call mid;\
                dd = 13 + d;\
            }\
            procedure left {\
                call right;\
                call right;\
                call right;\
            }\
            procedure right{\
                a = b;\
                b = c;\
                c = a;\
            }";

    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());

    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(19,18));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(18,17));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(17,19));

    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(10,13));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_affects_Bip(1,6));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_affects_Bip(4,9));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_affects_Bip(7,3));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_affects_Bip(11,13));
}

void Test_30_PKB_AffectsBip::test_AffectsBip_procBack()
{
        const string& simpleProg =
            "procedure main{\
                a = 1;\
                call two;\
                call three;\
                call four;\
                e = b+5;\
            }\
            procedure two{\
                call one;\
            }\
            procedure three{\
                call one;\
            }\
            procedure four{\
                call one;\
                d = c+9;\
            }\
            procedure one{\
                c = b + 10;\
                b = 11 + a;\
                call five;\
            }\
            procedure five{\
                b= 13;\
            }";
        // 13 -> 10 -> 9
        // 13 -> 5
        // 1 -> 11
        // 11 -/-> 10, 5

    string queryStr;
    set<int> intSet;
    SetWrapper<string> stringSet;
    Parser parser(simpleProg, FROMSTRING);
    parser.init();
    auto_ptr<PKB> pkb(parser.get_pkb());

    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(1,11));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(13,5));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(13,10));
    CPPUNIT_ASSERT_EQUAL(true,pkb->is_affects_Bip(10,9));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_affects_Bip(11,10));
    CPPUNIT_ASSERT_EQUAL(false,pkb->is_affects_Bip(11,5));

}


