#include <cstdio>
#include <cstdarg>
#include <string>
#include <map>
#include <set>
#include <list>
#include <utility>
#include "Test_10_Modifies.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::string;
using std::map;
using std::list;
using std::set;
using std::pair;
using std::make_pair;

void Test_10_Modifies::setUp()
{
    this->MODIFIES_01_PROG =
        "procedure pOne { \
           px = ty; \
           abc = sun; \
           if t then { \
             sun = rise; \
             while true { \
               heck = it + la; \
             } \
             pipe = dream; \
           } else { \
             dawn = now; \
             while smth { \
               snake = here; \
               if notTrue then { \
                 nobodyUses = 23; \
               } else { \
                 nobodyUses = abcd; \
               } \
             } \
           } \
           my = friend; \
           while germ { \
             sun = no + sun; \
           } \
           great = things; \
           come = hard; \
           call procTwo; \
         } \
         procedure procTwo { \
           hell = no; \
           while fine { \
             dont = heck; \
           } \
           no = go; \
           call procThree; \
         } \
         procedure procThree { \
           man = human; \
           whos = here; \
           hell = yes; \
         }";
}

void Test_10_Modifies::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_10_Modifies);

void Test_10_Modifies::test_modifies_single()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    simpleProg =
        "procedure procOne { \
           x = y + 3; \
           a = 5; \
           b = bad + amp + 41; \
           while itsTrue { \
             y = 5 + 6 + a; \
             if xab then { \
               kerb = s + 2; \
             } else { \
               big = trouble + 11; \
               a = a + a; \
             } \
             g2 = g1 + 1; \
             if bad then { \
               call ascP; \
               xyz = 123; \
             } else { \
               aa = aabbx; \
             } \
           } \
           call doSmth; \
           well = goodness - me; \
           if x then { \
             aa = ta; \
           } else { \
             aa = b; \
           } \
           xc = 3 + 56 + ab; \
         } \
         \
         procedure ascP { \
           if gax then { \
             xcz = 12; \
             while xg { \
               while bb { \
                 a = b + bad + good; \
                 well = bbz; \
               } \
               x = vv; \
             } \
             vv = 2 + g; \
           } else { \
             noway = yesway + 2; \
             x = 5; \
           } \
           hi = bye + 113; \
           thank = goodness; \
        } \
        \
        \
        \
        procedure doSmth { \
          yes = hell + no; \
          call cleanUp; \
          dont = do + this; \
        } \
        procedure cleanUp { \
          im = done; \
        }";

    // procOne
    // x, a, b, y, kerb, big, g2, xcz, well, vv, noway, hi, thank
    // xyz, aa, yes, im, dont, xc,

    // ascP
    // xcz, a, well, x, vv, noway, hi, thank

    // doSmth
    // yes, im, dont

    // cleanUp
    // im

    // procedure procOne
    // stmt 1 [assign] - x
    // stmt 2 [assign] - a
    // stmt 3 [assign] - b
    // stmt 4 [while] - y, kerb, big, a, g2, xcz, well, x, vv, noway, hi, thank,
    //                  xyz, aa
    // stmt 5 [assign] - y
    // stmt 6 [if] - kerb, big, a
    // stmt 7 [assign] - kerb
    // stmt 8 [assign] - big
    // stmt 9 [assign] - a
    // stmt 10 [assign] - g2
    // stmt 11 [if] - xcz, a, well, x, vv, noway, hi, thank, xyz, aa
    // stmt 12 [call ascP] - xcz, a, well, x, vv, noway, hi, thank
    // stmt 13 [assign] - xyz
    // stmt 14 [assign] - aa
    // stmt 15 [call doSmth] - yes, im, dont
    // stmt 16 [assign] - well
    // stmt 17 [if] - a
    // stmt 18 [assign] - aa
    // stmt 19 [assign] - aa
    // stmt 20 [assign] - xc

    // procedure ascP
    // stmt 21 [if] - xcz, a, well, x, vv, noway
    // stmt 22 [assign] - xcz
    // stmt 23 [while] - a, well, x
    // stmt 24 [while] - a, well
    // stmt 25 [assign] - a
    // stmt 26 [assign] - well
    // stmt 27 [assign] - x
    // stmt 28 [assign] - vv
    // stmt 29 [assign] - noway
    // stmt 30 [assign] - x
    // stmt 31 [assign] - hi
    // stmt 32 [assign] - thank

    // procedure doSmth
    // stmt 33 [assign] - yes
    // stmt 34 [call cleanUp] - im
    // stmt 35 [assign] - dont

    // procedure cleanUp
    // stmt 36 [assign] - im

    evaluator.parseSimple(simpleProg);
    // Modifies(assign,var)
    queryStr = "assign a; variable v; Select v such that Modifies(a,v)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(19, "x", "a", "b",
            "y", "kerb", "big", "g2", "xcz", "well", "vv", "noway",
            "hi", "thank", "xyz", "aa", "yes", "im", "dont", "xc"),
            stringSet);
    queryStr = "assign abb; variable jnah#; Select abb such that ";
    queryStr += " Modifies(abb, jnah#   \n)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(26, "1", "2", "3",
            "5", "7", "8", "9", "10", "13", "14", "16", "18", "19", "20",
            "22", "25", "26", "27", "28", "29", "30", "31", "32", "33",
            "35", "36"));
    // Modifies(procedure,var)
    queryStr = " procedure pla1; variable xyz; Select pla1 such that ";
    queryStr += " Modifies(pla1, xyz)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(4, "procOne",
            "ascP", "doSmth", "cleanUp"));
    // Modifies(call,var); Select call
    queryStr = " call ca1; variable vv; Select ca1 such that ";
    queryStr += " Modifies(ca1,vv)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "12", "15", "34"));
    // Modifies(call,var); Select call.stmt#
    queryStr = " call ba; variable v; Select ba.stmt# such that ";
    queryStr += " Modifies(ba,v)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "12", "15", "34"));
    // Modifies(call, var); Select call.procName
    queryStr = " call ab#as; variable xza; Select ab#as.procName such that ";
    queryStr += " Modifies(ab#as,  xza)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "ascP", "doSmth",
            "cleanUp"));
    // Modifies(call, var); Select var
    queryStr = " call aq1; variable hma; Select hma such that ";
    queryStr += " Modifies(aq1, hma)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(11, "xcz", "a",
            "well", "x", "vv", "noway", "hi", "thank", "yes", "im", "dont"));
    // Modifies(call, var); Select var.varName
    queryStr = " call uja1; variable baqw; Select baqw.varName such that ";
    queryStr += " Modifies(uja1, baqw)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(11, "xcz", "a",
            "well", "x", "vv", "noway", "hi", "thank", "yes", "im", "dont"));

    // Modifies(while, var); Select while
    queryStr = " while as; variable gaw; Select as such that ";
    queryStr += " Modifies(as, gaw)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "4", "23", "24"));
    // Modifies(while, var); Select while.stmt#
    queryStr = " while aa; variable yaa; Select aa.stmt# such that ";
    queryStr += " Modifies(aa,yaa)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(3, "4", "23", "24"));
    // Modifies(while, var); Select var
    queryStr = " while xaz1; variable hasdfS; Select hasdfS such that ";
    queryStr += " Modifies(xaz1, hasdfS)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(14, "a", "aa",
            "big", "g2", "hi", "kerb", "noway", "thank", "vv", "well",
            "x", "xcz", "xyz", "y"));
    // Modifies(while, var); Select var.varName
    queryStr = " while qw1; variable hHs; Select hHs.varName such that ";
    queryStr += " Modifies(qw1, hHs )";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(14, "a", "aa",
            "big", "g2", "hi", "kerb", "noway", "thank", "vv", "well",
            "x", "xcz", "xyz", "y"));

    // Modifies(if, var); Select if
    queryStr = "if ia1; variable vx; Select ia1 such that ";
    queryStr += " Modifies(ia1, vx)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(4, "6", "11", "17",
            "21"));
    // Modifies(if, var); Select if.stmt#
    queryStr = "if bas; variable vtrq; Select bas.stmt# such that ";
    queryStr += " Modifies(bas, vtrq)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(4, "6", "11", "17",
            "21"));
    // Modifies(if, var); Select var
    queryStr = " if cbj; variable kl; Select kl such that ";
    queryStr += " Modifies(cbj, kl)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(12, "a", "aa",
            "big", "hi", "kerb", "noway", "thank", "vv", "well", "x",
            "xcz", "xyz"));
    // Modifies(if, var); Select var.varName
    queryStr = " if ya; variable asd; Select asd.varName such that ";
    queryStr += " Modifies(ya, asd)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(12, "a", "aa",
            "big", "hi", "kerb", "noway", "thank", "vv", "well", "x",
            "xcz", "xyz"));

    // Modifies(stmt, var); Select stmt
    queryStr = "stmt s1; variable v11; Select s1 such that ";
    queryStr += " Modifies(s1, v11)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(36, "1", "2", "3",
            "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14",
            "15", "16", "17", "18", "19", "20", "21", "22", "23", "24",
            "25", "26", "27", "28", "29", "30", "31", "32", "33", "34",
            "35", "36"));
    // Modifies(stmt, var); Select stmt.stmt#
    queryStr = "stmt hga4; variable tas; Select hga4.stmt# such that ";
    queryStr += " Modifies(hga4, tas)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(36, "1", "2", "3",
            "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14",
            "15", "16", "17", "18", "19", "20", "21", "22", "23", "24",
            "25", "26", "27", "28", "29", "30", "31", "32", "33", "34",
            "35", "36"));
    // Modifies(stmt,var); Select var
    queryStr = " stmt sx; variable mh; Select mh such that ";
    queryStr += " Modifies(sx, mh)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(19, "a", "aa", "b",
            "big", "dont", "g2", "hi", "im", "kerb", "noway", "thank",
            "vv", "well", "x", "xc", "xcz", "xyz", "y", "yes"));
    // Modifies(stmt,var); Select var.varName
    queryStr = " stmt hgf; variable yw; Select yw.varName such that ";
    queryStr += " Modifies(hgf, yw)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(19, "a", "aa", "b",
            "big", "dont", "g2", "hi", "im", "kerb", "noway", "thank",
            "vv", "well", "x", "xc", "xcz", "xyz", "y", "yes"));

    // Modifies(prog_line, var); Select prog_line
    queryStr = " prog_line plgf; variable v11; Select plgf such that ";
    queryStr += " Modifies(plgf, v11)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(36, "1", "2", "3",
            "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14",
            "15", "16", "17", "18", "19", "20", "21", "22", "23", "24",
            "25", "26", "27", "28", "29", "30", "31", "32", "33", "34",
            "35", "36"));
    // Modifies(prog_line, var); Select prog_line.stmt#
    queryStr = "prog_line hga4; variable tas; Select hga4.stmt# such that ";
    queryStr += " Modifies(hga4, tas)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(36, "1", "2", "3",
            "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14",
            "15", "16", "17", "18", "19", "20", "21", "22", "23", "24",
            "25", "26", "27", "28", "29", "30", "31", "32", "33", "34",
            "35", "36"));
    // Modifies(prog_line,var); Select var
    queryStr = " prog_line sx; variable mh; Select mh such that ";
    queryStr += " Modifies(sx, mh)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(19, "a", "aa", "b",
            "big", "dont", "g2", "hi", "im", "kerb", "noway", "thank",
            "vv", "well", "x", "xc", "xcz", "xyz", "y", "yes"));
    // Modifies(prog_line,var); Select var.varName
    queryStr = " prog_line hgf; variable yw; Select yw.varName such that ";
    queryStr += " Modifies(hgf, yw)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(stringSet, SetWrapper<string>(19, "a", "aa", "b",
            "big", "dont", "g2", "hi", "im", "kerb", "noway", "thank",
            "vv", "well", "x", "xc", "xcz", "xyz", "y", "yes"));
}

void Test_10_Modifies::test_modifies_assign_var_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    // Uses(procedure,var)
    const string& simpleProg = this->MODIFIES_01_PROG;
    // vacuously correct but no choice for now
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a, a2; variable v1, v2; procedure p; ";
    queryStr += " Select a2 such that Modifies(a,v1) and Modifies(a2,v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a,v1)
    // (1,px), (2,abc), (4,sun), (6,heck), (7,pipe), (8,dawn), (10,snake)
    // (12,nobodyUses), (13,nobodyUses), (14,my), (16,sun),
    // (17,great), (18,come), (20,hell), (22,dont), (23,no),
    // (25,man), (26,whos), (27, hell)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(19, "1", "2", "4", "6",
            "7", "8", "10", "12", "13", "14", "16", "17", "18",
            "20", "22", "23", "25", "26", "27"),
            stringSet);
}

void Test_10_Modifies::test_modifies_proc_var_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    // Uses(procedure,var)
    const string& simpleProg = this->MODIFIES_01_PROG;
    // vacuously correct but no choice for now
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a, a2; variable v1, v2; procedure p; ";
    queryStr += " Select p such that Modifies(a,v1) and Modifies(p,v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a,v1)
    // (1,px), (2,abc), (4,sun), (6,heck), (7,pipe), (8,dawn), (10,snake)
    // (12,nobodyUses), (13,nobodyUses), (14,my), (16,sun),
    // (17,great), (18,come), (20,hell), (22,dont), (23,no),
    // (25,man), (26,whos), (27, hell)
    //
    // Modifies(p,v1)
    // a | v1 | p
    // (1,px,pOne), (2,abc,pOne), (4,sun,pOne), (6,heck,pOne),
    // (7,pipe,pOne), (8,dawn,pOne), (10,snake,pOne), (12,nobodyUses,pOne),
    // (13,nobodyUses,pOne), (14,my,pOne), (16,sun,pOne),
    // (17,great,pOne), (18,come,pOne), (20,hell,pOne),
    // (20,hell,procTwo), (20,hell,procThree), (22,dont,pOne),
    // (22,dont,procTwo),
    // (23,no,pOne), (23,no,procTwo), (25,man,pOne), (25,man,procTwo),
    // (25,man,procThree), (26,whos,pOne), (26,whos,procTwo),
    // (26,whos,procThree), (27,hell,pOne), (27,hell,procTwo),
    // (27,hell,procThree)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(3, "pOne", "procTwo",
            "procThree"),
            stringSet);
    // select whole table
    queryStr = "assign a, a2; variable v1, v2; procedure p; ";
    queryStr += " Select <a,v1,p> such that Modifies(a,v1) and ";
    queryStr += " Modifies(p,v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(29, "1,px,pOne", "2,abc,pOne",
            "4,sun,pOne", "6,heck,pOne", "7,pipe,pOne", "8,dawn,pOne",
            "10,snake,pOne",
            "12,nobodyUses,pOne", "13,nobodyUses,pOne", "14,my,pOne",
            "16,sun,pOne", "17,great,pOne", "18,come,pOne",
            "20,hell,pOne", "20,hell,procTwo", "20,hell,procThree",
            "22,dont,pOne",
            "22,dont,procTwo", "23,no,pOne", "23,no,procTwo",
            "25,man,pOne", "25,man,procTwo", "25,man,procThree",
            "26,whos,pOne", "26,whos,procTwo", "26,whos,procThree",
            "27,hell,pOne", "27,hell,procTwo", "27,hell,procThree"),
            stringSet);
}

void Test_10_Modifies::test_modifies_call_var_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->MODIFIES_01_PROG;
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a; variable v1, v2; call c; ";
    queryStr += " Select <a,v1,c> such that Modifies(a,v1) ";
    queryStr += " and Modifies(c,v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a,v1)
    // a | v1
    // (1,px), (2,abc), (4,sun), (6,heck), (7,pipe), (8,dawn), (10,snake)
    // (12,nobodyUses), (13,nobodyUses), (14,my), (16,sun),
    // (17,great), (18,come), (20,hell), (22,dont), (23,no),
    // (25,man), (26,whos), (27, hell)
    // ---
    // Modifies(c,v1)
    // a | v1 | c
    // (20,hell,19), (20,hell,24), (22,dont,19), (23,no,19), (25,man,19),
    // (25,man,24), (26,whos,19), (26,whos,24), (27,hell,19),
    // (27,hell,24)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(10, "20,hell,19", "20,hell,24",
            "22,dont,19", "23,no,19", "25,man,19", "25,man,24",
            "26,whos,19", "26,whos,24", "27,hell,19", "27,hell,24"),
            stringSet);
}

void Test_10_Modifies::test_modifies_while_var_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->MODIFIES_01_PROG;
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a; variable v1, v2; while w; ";
    queryStr += " Select <a,v1,w> such that Modifies(a,v1) ";
    queryStr += " and Modifies(w,v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a,v1)
    // a | v1
    // (1,px), (2,abc), (4,sun), (6,heck), (7,pipe), (8,dawn), (10,snake)
    // (12,nobodyUses), (13,nobodyUses), (14,my), (16,sun),
    // (17,great), (18,come), (20,hell), (22,dont), (23,no),
    // (25,man), (26,whos), (27, hell)
    // ---
    // Modifies(w,v1)
    // a | v1 | w
    // (4,sun,13), (6,heck,5), (10,snake,9), (12,nobodyUses,9)
    // (13,nobodyuses,9), (16,sun,15), (22,dont,21)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(7, "4,sun,15", "6,heck,5",
            "10,snake,9", "12,nobodyUses,9", "13,nobodyUses,9",
            "16,sun,15", "22,dont,21"),
            stringSet);
}

void Test_10_Modifies::test_modifies_if_var_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->MODIFIES_01_PROG;
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a; variable v1, v2; if if1; ";
    queryStr += " Select <a,v1,if1> such that Modifies(a,v1) and ";
    queryStr += " Modifies(if1,v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a,v1)
    // a | v1
    // (1,px), (2,abc), (4,sun), (6,heck), (7,pipe), (8,dawn), (10,snake)
    // (12,nobodyUses), (13,nobodyUses), (14,my), (16,sun),
    // (17,great), (18,come), (20,hell), (22,dont), (23,no),
    // (25,man), (26,whos), (27, hell)
    // ---
    // Modifies(if1,v1)
    // a | v1 | if1
    // (4,sun,3), (6,heck,3), (7,pipe,3), (8,dawn,3), (10,snake,3)
    // (12,nobodyUses,3), (12,nobodyUses,11), (13,nobodyUses,3),
    // (13,nobodyUses,11), (16,sun,3)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(10, "4,sun,3", "6,heck,3",
            "7,pipe,3", "8,dawn,3", "10,snake,3", "12,nobodyUses,3",
            "12,nobodyUses,11", "13,nobodyUses,3", "13,nobodyUses,11",
            "16,sun,3"),
            stringSet);
}

void Test_10_Modifies::test_modifies_stmt_var_01()
{
    string queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    const string& simpleProg = this->MODIFIES_01_PROG;
    evaluator.parseSimple(simpleProg);
    queryStr = "assign a; variable v1, v2; stmt s1; ";
    queryStr += " Select <a,v1,s1> such that Modifies(a,v1) and ";
    queryStr += " Modifies(s1,v1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    // Modifies(a,v1)
    // a | v1
    // (1,px), (2,abc), (4,sun), (6,heck), (7,pipe), (8,dawn), (10,snake)
    // (12,nobodyUses), (13,nobodyUses), (14,my), (16,sun),
    // (17,great), (18,come), (20,hell), (22,dont), (23,no),
    // (25,man), (26,whos), (27, hell)
    // ---
    // Modifies(s1,v1)
    // a | v1 | s1
    // (1,px,1), (2,abc,2), (4,sun,3), (4,sun,4), (4,sun,15)
    // (4,sun,16), (6,heck,3), (6,heck,5), (6,heck,6), (7,pipe,3)
    // (7,pipe,7), (8,dawn,3), (8,dawn,8), (10,snake,3), (10,snake,9)
    // (10,snake,10), (12,nobodyUses,3),  (12,nobodyUses,9),
    // (12,nobodyUses,11), (12,nobodyUses,12), (12,nobodyUses,13),
    // (13,nobodyUses,3), (13,nobodyUses,9), (13,nobodyUses,11)
    // (13,nobodyUses,12), (13,nobodyUses,13), (14,my,14), (16,sun,3)
    // (16,sun,4), (16,sun,15), (16,sun,16), (17,great,17), (18,come,18)
    // (20,hell,19), (20,hell,20), (20,hell,24), (20,hell,27)
    // (22,dont,19), (22,dont,21), (22,dont,22), (23,no,19)
    // (23,no,23), (25,man,19), (25,man,24), (25,man,25), (26,whos,19)
    // (26,whos,24), (26,whos,26), (27,hell,19), (27,hell,20)
    // (27,hell,24), (27,hell,27)
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(52, "1,px,1", "2,abc,2",
            "4,sun,3", "4,sun,4", "4,sun,15", "4,sun,16", "6,heck,3",
            "6,heck,5", "6,heck,6", "7,pipe,3", "7,pipe,7", "8,dawn,3",
            "8,dawn,8", "10,snake,3", "10,snake,9", "10,snake,10",
            "12,nobodyUses,3", "12,nobodyUses,9", "12,nobodyUses,11",
            "12,nobodyUses,12", "12,nobodyUses,13", "13,nobodyUses,3",
            "13,nobodyUses,9", "13,nobodyUses,11", "13,nobodyUses,12",
            "13,nobodyUses,13", "14,my,14", "16,sun,3", "16,sun,4",
            "16,sun,15", "16,sun,16", "17,great,17", "18,come,18",
            "20,hell,19", "20,hell,20", "20,hell,24", "20,hell,27",
            "22,dont,19", "22,dont,21", "22,dont,22", "23,no,19",
            "23,no,23", "25,man,19", "25,man,24", "25,man,25",
            "26,whos,19", "26,whos,24", "26,whos,26", "27,hell,19",
            "27,hell,20", "27,hell,24", "27,hell,27"),
            stringSet);
}