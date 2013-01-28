#include <string>
#include <set>
#include <list>
#include "Test_20_SynSyn_RelRef.h"
#include "../SPA/SetWrapper.h"
#include "../SPA/QueryEvaluator.h"

using std::string;
using std::set;
using std::list;

void Test_20_SynSyn_RelRef::setUp() {}

void Test_20_SynSyn_RelRef::tearDown() {}

CPPUNIT_TEST_SUITE_REGISTRATION(Test_20_SynSyn_RelRef);

void Test_20_SynSyn_RelRef::test_uses_modifies_same_variable()
{
    string simpleProg, queryStr;
    list<string> resultList;
    SetWrapper<string> stringSet;
    QueryEvaluator evaluator;

    simpleProg =
        "procedure Pone { \
           apple = orange; \
           x5 = 2 + ab + 7; \
           while i { \
             ab = mk + yong; \
             apple = 5; \
           } \
           x = x5 + c2; \
           if p then { \
             call PTwo; \
           } else { \
             inscope = here + x5; \
           } \
           twoB = 1 + 3 + 7; \
         } \
         procedure PTwo { \
           end = game; \
           hates = apple * ab; \
           fun = stuff + goods; \
           if true then { \
             fear = this; \
           } else { \
             this = train; \
           } \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "assign ahh, mbb; variable vv1; Select <mbb, vv1> ";
    queryStr += " such that Modifies(ahh, vv1) and Uses(mbb, vv1)";
    evaluator.evaluate(queryStr, resultList);
    // variables both used and modified by assign:
    //   apple, x5, ab, this
    // assignment that uses them:
    //   apple [12], x5 [6, 9], ab [2, 12], this [15]
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(20, "2,apple", "2,x5",
            "2,ab", "2,this", "6,apple", "6,x5", "6,ab", "6,this",
            "9,apple", "9,x5", "9,ab", "9,this", "12,apple", "12,x5",
            "12,ab", "12,this", "15,apple", "15,x5", "15,ab", "15,this"),
            stringSet);
}

void Test_20_SynSyn_RelRef::test_ev_rr_ss_string_string_00_from_argOne()
{
    string simpleProg, queryStr;
    list<string> resultList;
    SetWrapper<string> stringSet;
    QueryEvaluator evaluator;

    simpleProg =
        "procedure evRRss { \
           a = b + cd - efg; \
           iOne = iTwo + ple; \
           while i { \
             mm = 2 + 35 - 63; \
             if well then { \
               no = choice; \
             } else { \
               thats = what + youve + got; \
             } \
             be = a - man; \
           } \
           my = friend; \
         } \
         procedure twoProc { \
           yes = man; \
           obey = the + command; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "procedure psa; variable jsa; Select <psa,jsa> such that ";
    queryStr += " Modifies(psa,jsa)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(18, "evRRss,a", "evRRss,iOne",
            "evRRss,mm", "evRRss,no", "evRRss,thats", "evRRss,be",
            "evRRss,my", "evRRss,yes", "evRRss,obey", "twoProc,a",
            "twoProc,iOne", "twoProc,mm", "twoProc,no", "twoProc,thats",
            "twoProc,be", "twoProc,my", "twoProc,yes", "twoProc,obey"),
            stringSet);
}

void Test_20_SynSyn_RelRef::test_ev_rr_ss_string_string_01()
{
    string simpleProg, queryStr;
    list<string> resultList;
    SetWrapper<string> stringSet;
    QueryEvaluator evaluator;

    simpleProg =
        "procedure firstProc { \
           a1 = hot + day; \
           if i then { \
             me = too; \
           } else { \
             assign = due; \
           } \
           hello = byebye + static; \
         } \
         procedure secProc { \
           static = analysis; \
           while m { \
             what = now; \
             nobody = is + answering - me; \
             if you then { \
               can = see; \
               thenIs = good; \
             } else { \
               otherwise = good + luck + to - me; \
             } \
           } \
         } ";
    queryStr = " assign bhb; variable tax; procedure Mira; ";
    queryStr += " Select <tax,Mira> such that Modifies(bhb, tax) ";
    queryStr += " and Uses(Mira, tax)";
    // Variables modified by assignment:
    //   a1, assign, can, hello, me, nobody, otherwise, static,
    //   thenIs, what
    // Variables above that are used by some procedure:
    //   me [secProc], static [firstProc]
    // Procedures: firstProc, secProc
    evaluator.parseSimple(simpleProg);
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "me,firstProc",
            "static,firstProc", "me,secProc", "static,secProc"),
            stringSet);
}

void Test_20_SynSyn_RelRef::test_ev_rr_ss_string_string_10()
{
    string simpleProg, queryStr;
    list<string> resultList;
    SetWrapper<string> stringSet;
    QueryEvaluator evaluator;

    // Modifies(proc,var1), Uses(proc,var2)
    simpleProg =
        "procedure Aleph { \
           song = of + burchess; \
           if nice then { \
             clap = your + hands; \
             while xt { \
               aa = bb; \
             } \
           } else { \
             melody = noise; \
           } \
           alittle = tired; \
         } \
         procedure GDay { \
           good = morning; \
           my = friends; \
           if cool then { \
             bb = alittle; \
           } else { \
             noise = met; \
           } \
         } \
         procedure UsesNothing { \
           this = 1 + 3; \
           proc = 5 + 7 - 162; \
           uses = 742; \
           nothing = 864 + 721; \
         } \
         procedure UseFromCall { \
           use = 73; \
           from = 1246; \
           call GDay; \
         }";
    queryStr = "procedure asdf1; variable V1gds, Vjju; ";
    queryStr += " Select asdf1 such that Modifies(asdf1,V1gds) and ";
    queryStr += " Uses(asdf1, Vjju)";
    evaluator.parseSimple(simpleProg);
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(
            SetWrapper<string>(3, "Aleph", "GDay", "UseFromCall"),
            stringSet);
}

void Test_20_SynSyn_RelRef::test_ev_rr_ss_string_string_11()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    simpleProg =
        "procedure Aone { \
           today = is + sunday; \
           i = am + coding - today; \
           while true { \
             this = is + an; \
             infinite = loop; \
             if my then { \
               teammates = can + help; \
               it = will - be * good; \
             } else { \
               but = they + just - cant; \
               help = me; \
             } \
             so = i + have; \
             to = solo; \
           } \
           end = time; \
         } \
         procedure storyCont { \
           you = will - not; \
           notice = this + message; \
           but = you + will - browse; \
           the = code; \
         } \
         procedure noCount { \
           my = 1; \
           a = 2; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = "procedure pavaA1; variable GJA; Select <pavaA1, GJA> ";
    queryStr += " such that Modifies(pavaA1, GJA) and Uses(pavaA1, GJA)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(12, "Aone,help", "Aone,i",
            "Aone,my", "Aone,this", "Aone,today", "Aone,you",
            "storyCont,help", "storyCont,i", "storyCont,my",
            "storyCont,this", "storyCont,today", "storyCont,you"),
            stringSet);
}

void Test_20_SynSyn_RelRef::test_ev_rr_ss_int_string_00_from_argOne()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    simpleProg =
        "procedure toDo { \
           term = factor + factor; \
           if fault then { \
             version = control; \
           } else { \
             numb = to + pain; \
           } \
           numb = yes; \
         } \
         procedure explodeStr { \
           monotonic = increasing + function; \
           complete = lattice - ascending; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " assign a12; variable Tgs; Select <a12, Tgs> ";
    queryStr += " such that Modifies(a12, Tgs)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(30, "1,term", "1,version",
            "1,numb", "1,monotonic", "1,complete", "3,term", "3,version",
            "3,numb", "3,monotonic", "3,complete", "4,term", "4,version",
            "4,numb", "4,monotonic", "4,complete", "5,term", "5,version",
            "5,numb", "5,monotonic", "5,complete", "6,term", "6,version",
            "6,numb", "6,monotonic", "6,complete", "7,term", "7,version",
            "7,numb", "7,monotonic", "7,complete"),
            stringSet);
}

void Test_20_SynSyn_RelRef::test_ev_rr_ss_int_string_01()
{
    string simpleProg, queryStr;
    QueryEvaluator evaluator;
    list<string> resultList;
    SetWrapper<string> stringSet;

    simpleProg =
        "procedure iiProc { \
           test = pyramid; \
           white = box + testing; \
           unit = test; \
           while notTested { \
             unit = test - cases; \
             interactions = scenario; \
             less = integration; \
           } \
           blackbox = testing; \
         } \
         procedure burnMoney { \
           never = productive; \
           dont = test + function; \
           at = scheme - of * app; \
           select = white; \
         }";
    evaluator.parseSimple(simpleProg);
    queryStr = " assign axc, aeEx; variable pib#1; ";
    queryStr += " Select <aeEx, pib#1> such that Modifies(aeEx,pib#1) ";
    queryStr += " and Uses(axc, pib#1)";
    evaluator.evaluate(queryStr, resultList);
    stringSet = SetWrapper<string>(resultList);
    CPPUNIT_ASSERT_EQUAL(SetWrapper<string>(4, "1,test", "1,white",
            "2,test", "2,white"),
            stringSet);
}