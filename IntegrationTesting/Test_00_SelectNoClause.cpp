#include <string>
#include <set>
#include <list>
#include "Test_00_SelectNoClause.h"
#include "../SPA/QueryEvaluator.h"

using std::string;
using std::set;
using std::list;

void Test_00_SelectNoClause::setUp() {}
void Test_00_SelectNoClause::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_00_SelectNoClause);

void Test_00_SelectNoClause::test_select_one_syn()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    set<string> stringSet;
    simpleProg =
        "procedure pOne { \n\
           a = b + cd; \
           g = a * xc; \
           if i then { \
             true = 0; \
             while xp { \
               good = evil + bad; \
               call twoProng; \
               while cd { \n\
                 blah = f; \
                 if gt then { \
                   hi = bye; \n \
                 } else { \
                   no = tify; \
                 } \
                 down = out; \
               } \
               hell = yea; \
               call GGG; \
             } \
             good = good; \
             heat = sink + 55; \
           } else { \
             i = am + evil; \
             while two { \
               eye = ee; \
             } \
           } \
           tree = ish; \
         } \n\
         procedure twoProng { \n \
           harryPottter = not - harryPuttar; \
           if x then { \
             y = aa + gadfly; \
           } else { \
             red = yellow + orange; \
           }\
         }\
         procedure GGG { \
           gg = ggGGggGG; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "assign asdfa; Select asdfa";
    evaluator.evaluate(queryStr, resultList);
    stringSet = set<string>(resultList.begin(), resultList.end());
    this->compare_string_set(stringSet, 18, "1", "2", "4", "6", "9", "11",
            "12", "13", "14", "16", "17", "18", "20", "21", "22", "24",
            "25", "26");
}