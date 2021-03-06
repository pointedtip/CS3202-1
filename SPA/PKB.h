#ifndef T11_PKB_H
#define T11_PKB_H
#include <map>
#include <set>
#include <string>
#include <queue>
#include <stack>
#include <utility>
#include "PQL.h"
#include "ProcTable.h"
#include "VarTable.h"
#include "Node.h"
#include "StmtBank.h"
#include "CFGNode.h"


using std::map;
using std::set;
using std::string;
using std::queue;
using std::stack;
using std::pair;


 ///Stores the various data structures and answers queries from the QE
class PKB{


public:
    PKB();
    PKB(Node *root, ProcTable *pt, VarTable *vt, StmtBank *sb, vector<CFGNode*> *cfg);

    /**
     * Modifies(X,var); Retrieves all var modified by X, where X is
     * a synonym represented by integers.
     * @param xType type of X
     * @param yType type of Y. This can only be ENT_VAR
     * @return a set of variable names modified by X
     */
    std::set<std::string> modifies_X_Y_get_string_Y_from_int_X
        (DesignEnt xType, DesignEnt yType, int stmt) const;
    /**
     * Modifies(X,var); Retrieves all var modified by X, where X is
     * a synonym represented by strings.
     * @param yType type of Y. This can only be ENT_VAR
     * @return a set of variable names modified by X
     */
    std::set<std::string> modifies_X_Y_get_string_Y_from_string_X
        (DesignEnt xType, DesignEnt yType, const std::string& x) const;
    /**
     * Modifies(X,var); Given a varname, retrieves all X modifying it,
     * where X is a synonym with integer values.
     * @param xType type of X
     * @param yType type of Y. This can only be ENT_VAR
     * @param varName variable name
     * @return a set of integers representing synonym X modifying the var
     */
    std::set<int> modifies_X_Y_get_int_X_from_string_Y(DesignEnt xType,
            DesignEnt yType, const std::string& varName) const;
    /**
     * Modifies(X,var); Given a varname, retrieves all X modifying it,
     * where X is a synonym with string values.
     * @param xType type of X
     * @param yType type of Y. This can only be ENT_VAR
     * @param varName variable name
     * @return a set of strings representing synonym X modifying the var
     */
    std::set<std::string> modifies_X_Y_get_string_X_from_string_Y
            (DesignEnt xType, DesignEnt yType,
                const std::string& varName) const;
    /**
     * Given X (string) and Y (string), checks if Modifies(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param yType type of Y
     * @param y value of Y
     * @return true if Modifies(X,Y), false otherwise
     */
    bool modifies_query_string_X_string_Y(DesignEnt xType,
            const std::string& x, DesignEnt yType, const std::string& y)
                const;

    /**
     * Returns true if Modifies(X,_)
     * @param xType type of X
     * @param x statement number of X
     * @return true if Modifies(X,_), false otherwise
     */
    bool modifies_X_Y_int_X_smth(DesignEnt xType, int x) const;

    /**
     * Returns true if Modifies(X,_)
     * @param xType type of X
     * @param x string representing X
     * @return true if Modifies(X,_), false otherwise
     */
    bool modifies_X_Y_string_X_smth(DesignEnt xType,
            const std::string& x) const;

    /**
     * Returns true if Modifies(_,Y)
     * @param yType type of Y
     * @param y string representing Y
     * @return true if Modifies(_,Y), false otherwise
     */
    bool modifies_X_Y_smth_string_Y(DesignEnt yType,
            const std::string& y) const;

    /**
     * Given X (int) and Y (string), checks if Modifies(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param yType type of Y
     * @param y value of Y
     * @return true if Modifies(X,Y), false otherwise
     */
    bool modifies_query_int_X_string_Y(DesignEnt xType,
            int x, DesignEnt yType, const std::string& y)
                const;

    /**
     * Uses(X,Y); given synonym Y (string), retrieve all X (int)
     * such that Uses(X,Y) holds.
     * @param xType type of X
     * @param yType type of Y. This can only be ENT_VAR
     * @param varName variable name of Y
     * @return set of X such that Uses(X,Y)
     */
    std::set<int> uses_X_Y_get_int_X_from_string_Y(DesignEnt xType,
            DesignEnt yType, const std::string& varName) const;
    /**
     * Uses(X,Y); given synonym Y (string), retrieve all X (string)
     * such that Uses(X,Y) holds.
     * @param xType type of X
     * @param yType type of Y. This can only be ENT_VAR
     * @param varName variable name of Y
     * @return set of X such that Uses(X,Y)
     */
    std::set<std::string> uses_X_Y_get_string_X_from_string_Y
            (DesignEnt xType, DesignEnt yType,
                const std::string& varName) const;
    /**
     * Uses(X,Y); given synonym X (int), retrieve all Y (string)
     * such that Uses(X,Y) holds.
     * @param xType type of X
     * @param yType type of Y. This can only be ENT_VAR
     * @param stmtNo statement number of X
     * @return set of Y such that Uses(X,Y)
     */
    std::set<std::string> uses_X_Y_get_string_Y_from_int_X
            (DesignEnt xType, DesignEnt yType, int stmtNo) const;
    /**
     * Uses(X,Y); given synonym X (string), retrieve all Y (string)
     * such that Uses(X,Y) holds.
     * @param xType type of X
     * @param yType type of Y. This can only be ENT_VAR
     * @param x string value of X
     * @return set of Y such that Uses(X,Y)
     */
    std::set<std::string> uses_X_Y_get_string_Y_from_string_X
            (DesignEnt xType, DesignEnt yType,
                const std::string& x) const;
    /**
     * Given X (string) and Y (string), checks if Uses(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param yType type of Y
     * @param y value of Y
     * @return true if Uses(X,Y), false otherwise
     */
    bool uses_query_string_X_string_Y(DesignEnt xType,
            const std::string& x, DesignEnt yType, const std::string& y)
                const;

    /**
     * Given X (int) and Y (string), checks if Uses(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param yType type of Y
     * @param y value of Y
     * @return true if Uses(X,Y), false otherwise
     */
    bool uses_query_int_X_string_Y(DesignEnt xType, int x,
            DesignEnt yType, const std::string& y) const;

    /**
     * Returns true if Uses(X,_)
     * @param xType type of X
     * @param x statement number of X
     * @return true if Uses(X,_), false otherwise
     */
    bool uses_X_Y_int_X_smth(DesignEnt xType, int x) const;

    /**
     * Returns true if Uses(X,_)
     * @param xType type of X
     * @param x string representing X
     * @return true if Uses(X,_), false otherwise
     */
    bool uses_X_Y_string_X_smth(DesignEnt xType,
            const std::string& x) const;

    /**
     * Returns true if Uses(_,Y)
     * @param yType type of Y
     * @param y string representing Y
     * @return true if Uses(_,Y), false otherwise
     */
    bool uses_X_Y_smth_string_Y(DesignEnt yType,
            const std::string& y) const;

    /**
     * Checks if there is at least one Uses Relation in the PKB
     * @return true if Uses(_,_), false otherwise
     */
    bool uses_X_Y_smth_smth() const;

    /**
     * Calls(X,Y); given Y (string), get all X (string) such that
     * Calls(X,Y)
     * @param xType type of X
     * @param yType type of Y
     * @param y string value of Y
     * @return set of X (string) such that Calls(X,Y)
     */
    std::set<std::string> calls_X_Y_get_string_X_from_string_Y
            (DesignEnt xType, DesignEnt yType,
                const std::string& y) const;

    /**
     * Calls(X,Y); given X (string), get all Y (string) such that
     * Calls(X,Y)
     * @param xType type of X
     * @param yType type of Y
     * @param x string value of X
     * @return set of Y (string) such that Calls(X,Y)
     */
    std::set<std::string> calls_X_Y_get_string_Y_from_string_X
            (DesignEnt xType, DesignEnt yType,
                const std::string& x) const;

    /**
     * Given X (string) and Y (string), checks if Calls(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param yType type of Y
     * @param y value of Y
     * @return true if Calls(X,Y), false otherwise
     */
    bool calls_query_string_X_string_Y(DesignEnt xType,
            const std::string& x, DesignEnt yType, const std::string& y)
                const;

    /**
     * Returns true if Calls(X,_)
     * @param xType type of X
     * @param x string representing X
     * @return true if Calls(X,_), false otherwise
     */
    bool calls_X_Y_string_X_smth(DesignEnt xType,
            const std::string& x) const;

    /**
     * Returns true if Calls(_,Y)
     * @param yType type of Y
     * @param y string representing Y
     * @return true if Calls(_,Y), false otherwise
     */
    bool calls_X_Y_smth_string_Y(DesignEnt yType,
            const std::string& y) const;

    /**
     * Calls*(X,Y); given Y (string), get all X (string) such that
     * Calls*(X,Y)
     * @param xType type of X
     * @param yType type of Y
     * @param y string value of Y
     * @return set of X (string) such that Calls*(X,Y)
     */
    std::set<std::string> callsStar_X_Y_get_string_X_from_string_Y
            (DesignEnt xType, DesignEnt yType,
                const std::string& y) const;
    /**
     * Calls*(X,Y); given X (string), get all Y (string) such that
     * Calls*(X,Y)
     * @param xType type of X
     * @param yType type of Y
     * @param x string value of X
     * @return set of Y (string) such that Calls*(X,Y)
     */
    std::set<std::string> callsStar_X_Y_get_string_Y_from_string_X
            (DesignEnt xType, DesignEnt yType,
                const std::string& x) const;

    /**
     * Given X (string) and Y (string), checks if Calls*(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param yType type of Y
     * @param y value of Y
     * @return true if Calls*(X,Y), false otherwise
     */
    bool callsStar_query_string_X_string_Y(DesignEnt xType,
            const std::string& x, DesignEnt yType, const std::string& y)
                const;

    /**
     * Returns true if Calls*(X,_)
     * @param xType type of X
     * @param x string representing X
     * @return true if Calls*(X,_), false otherwise
     */
    bool callsStar_X_Y_string_X_smth(DesignEnt xType,
            const std::string& x) const;

    /**
     * Returns true if Calls*(_,Y)
     * @param yType type of Y
     * @param y string representing Y
     * @return true if Calls*(_,Y), false otherwise
     */
    bool callsStar_X_Y_smth_string_Y(DesignEnt yType,
            const std::string& y) const;

    /**
     * Parent(X,Y); given Y (int), retrieve all X (int) such that
     * Parent(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that Parent(X,Y)
     */
    std::set<int> parent_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;
    /**
     * Parent(X,Y); given X (int), retrieve all Y (int) such that
     * Parent(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that Parent(X,Y)
     */
    std::set<int> parent_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;

    /**
     * Given X (int) and Y (int), checks if Parent(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param yType type of Y
     * @param y value of Y
     * @return true if Parent(X,Y), false otherwise
     */
    bool parent_query_int_X_int_Y(DesignEnt xType,
            int x, DesignEnt yType, int y) const;

    /**
     * Returns true if Parent(X,_)
     * @param xType type of X
     * @param x statement number of X
     * @return true if Parent(X,_), false otherwise
     */
    bool parent_X_Y_int_X_smth(DesignEnt xType, int x) const;

    /**
     * Returns true if Parent(_,Y)
     * @param xType type of Y
     * @param x statement number of Y
     * @return true if Parent(_,Y), false otherwise
     */
    bool parent_X_Y_smth_int_Y(DesignEnt yType, int y) const;

    /**
     * Parent*(X,Y); given Y (int), retrieve all X (int) such that
     * Parent*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that Parent*(X,Y)
     */
    std::set<int> parentStar_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;
    /**
     * Parent*(X,Y); given X (int), retrieve all Y (int) such that
     * Parent*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that Parent*(X,Y)
     */
    std::set<int> parentStar_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;

    /**
     * Given X (int) and Y (int), checks if Parent*(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param yType type of Y
     * @param y value of Y
     * @return true if Parent*(X,Y), false otherwise
     */
    bool parentStar_query_int_X_int_Y(DesignEnt xType,
            int x, DesignEnt yType, int y) const;

    /**
     * Returns true if Parent*(X,_)
     * @param xType type of X
     * @param x statement number of X
     * @return true if Parent*(X,_), false otherwise
     */
    bool parentStar_X_Y_int_X_smth(DesignEnt xType, int x) const;

    /**
     * Returns true if Parent*(_,Y)
     * @param xType type of Y
     * @param x statement number of Y
     * @return true if Parent*(_,Y), false otherwise
     */
    bool parentStar_X_Y_smth_int_Y(DesignEnt yType, int y) const;

    /**
     * Follows(X,Y); given Y (int), retrieve all X (int) such that
     * Follows(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that Follows(X,Y)
     */
    std::set<int> follows_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;
    /**
     * Follows(X,Y); given X (int), retrieve all Y (int) such that
     * Follows(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that Follows(X,Y)
     */
    std::set<int> follows_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;

    /**
     * Given X (int) and Y (int), checks if Follows(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param yType type of Y
     * @param y value of Y
     * @return true if Follows(X,Y), false otherwise
     */
    bool follows_query_int_X_int_Y(DesignEnt xType,
            int x, DesignEnt yType, int y) const;

    /**
     * Returns true if Follows(X,_)
     * @param xType type of X
     * @param x statement number of X
     * @return true if Follows(X,_), false otherwise
     */
    bool follows_X_Y_int_X_smth(DesignEnt xType, int x) const;

    /**
     * Returns true if Follows(_,Y)
     * @param xType type of Y
     * @param x statement number of Y
     * @return true if Follows(_,Y), false otherwise
     */
    bool follows_X_Y_smth_int_Y(DesignEnt yType, int y) const;

    /**
     * Follows*(X,Y); given Y (int), retrieve all X (int) such that
     * Follows*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that Follows*(X,Y)
     */
    std::set<int> followsStar_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;
    /**
     * Follows*(X,Y); given X (int), retrieve all Y (int) such that
     * Follows*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that Follows*(X,Y)
     */
    std::set<int> followsStar_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;

    /**
     * Given X (int) and Y (int), checks if Follows*(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param yType type of Y
     * @param y value of Y
     * @return true if Follows*(X,Y), false otherwise
     */
    bool followsStar_query_int_X_int_Y(DesignEnt xType,
            int x, DesignEnt yType, int y) const;

    /**
     * Returns true if Follows*(X,_)
     * @param xType type of X
     * @param x statement number of X
     * @return true if Follows*(X,_), false otherwise
     */
    bool followsStar_X_Y_int_X_smth(DesignEnt xType, int x) const;

    /**
     * Returns true if Follows*(_,Y)
     * @param xType type of Y
     * @param x statement number of Y
     * @return true if Follows*(_,Y), false otherwise
     */
    bool followsStar_X_Y_smth_int_Y(DesignEnt yType, int y) const;

    /**
     * Next(X,Y); given Y (int), retrieve all X (int) such that
     * Next(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that Next(X,Y)
     */
    std::set<int> next_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;
    /**
     * Next(X,Y); given X (int), retrieve all Y (int) such that
     * Next(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that Next(X,Y)
     */
    std::set<int> next_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;

    /**
     * Given X (int) and Y (int), checks if Next(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param yType type of Y
     * @param y value of Y
     * @return true if Next(X,Y), false otherwise
     */
    bool next_query_int_X_int_Y(DesignEnt xType,
            int x, DesignEnt yType, int y) const;

    /**
     * Returns true if Next(X,_)
     * @param xType type of X
     * @param x statement number of X
     * @return true if Next(X,_), false otherwise
     */
    bool next_X_Y_int_X_smth(DesignEnt xType, int x) const;

    /**
     * Returns true if Next(_,Y)
     * @param xType type of Y
     * @param x statement number of Y
     * @return true if Next(_,Y), false otherwise
     */
    bool next_X_Y_smth_int_Y(DesignEnt yType, int y) const;

    /**
     * Next*(X,Y); given Y (int), retrieve all X (int) such that
     * Next*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that Next*(X,Y)
     */
    std::set<int> nextStar_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;
    /**
     * Next*(X,Y); given X (int), retrieve all Y (int) such that
     * Next*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that Next*(X,Y)
     */
    std::set<int> nextStar_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;

    /**
     * Given X (int) and Y (int), checks if Next*(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param yType type of Y
     * @param y value of Y
     * @return true if Next*(X,Y), false otherwise
     */
    bool nextStar_query_int_X_int_Y(DesignEnt xType,
            int x, DesignEnt yType, int y) const;

    /**
     * Returns true if Next*(X,_)
     * @param xType type of X
     * @param x statement number of X
     * @return true if Next*(X,_), false otherwise
     */
    bool nextStar_X_Y_int_X_smth(DesignEnt xType, int x) const;

    /**
     * Returns true if Next*(_,Y)
     * @param xType type of Y
     * @param x statement number of Y
     * @return true if Next*(_,Y), false otherwise
     */
    bool nextStar_X_Y_smth_int_Y(DesignEnt yType, int y) const;

    /**
     * NextBip(X,Y); given Y (int), retrieve all X (int) such that
     * NextBip(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that NextBip(X,Y)
     */
    std::set<int> nextBip_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;
    /**
     * NextBip(X,Y); given X (int), retrieve all Y (int) such that
     * NextBip(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that NextBip(X,Y)
     */
    std::set<int> nextBip_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;

    /**
     * Given X (int) and Y (int), checks if NextBip(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param yType type of Y
     * @param y value of Y
     * @return true if NextBip(X,Y), false otherwise
     */
    bool nextBip_query_int_X_int_Y(DesignEnt xType,
            int x, DesignEnt yType, int y) const;

    /**
     * Returns true if NextBip(X,_)
     * @param xType type of X
     * @param x statement number of X
     * @return true if NextBip(X,_), false otherwise
     */
    bool nextBip_X_Y_int_X_smth(DesignEnt xType, int x) const;

    /**
     * Returns true if NextBip(_,Y)
     * @param xType type of Y
     * @param x statement number of Y
     * @return true if NextBip(_,Y), false otherwise
     */
    bool nextBip_X_Y_smth_int_Y(DesignEnt yType, int y) const;

    /**
     * NextBip*(X,Y); given Y (int), retrieve all X (int) such that
     * NextBip*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that NextBip*(X,Y)
     */
    std::set<int> nextBipStar_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;
    /**
     * NextBip*(X,Y); given X (int), retrieve all Y (int) such that
     * NextBip*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that NextBip*(X,Y)
     */
    std::set<int> nextBipStar_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;

    /**
     * Given X (int) and Y (int), checks if NextBip*(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param yType type of Y
     * @param y value of Y
     * @return true if NextBip*(X,Y), false otherwise
     */
    bool nextBipStar_query_int_X_int_Y(DesignEnt xType,
            int x, DesignEnt yType, int y) const;

    /**
     * Returns true if NextBip*(X,_)
     * @param xType type of X
     * @param x statement number of X
     * @return true if NextBip*(X,_), false otherwise
     */
    bool nextBipStar_X_Y_int_X_smth(DesignEnt xType, int x) const;

    /**
     * Returns true if NextBip*(_,Y)
     * @param xType type of Y
     * @param x statement number of Y
     * @return true if NextBip*(_,Y), false otherwise
     */
    bool nextBipStar_X_Y_smth_int_Y(DesignEnt yType, int y) const;

    /**
     * Affects(X,Y); given Y (int), retrieve all X (int) such that
     * Affects(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that Affects(X,Y)
     */
    std::set<int> affects_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;
    /**
     * Affects(X,Y); given X (int), retrieve all Y (int) such that
     * Affects(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that Affects(X,Y)
     */
    std::set<int> affects_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;

    /**
     * Given X (int) and Y (int), checks if Affects(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param yType type of Y
     * @param y value of Y
     * @return true if Affects(X,Y), false otherwise
     */
    bool affects_query_int_X_int_Y(DesignEnt xType,
            int x, DesignEnt yType, int y) const;

    /**
     * Returns true if Affects(X,_)
     * @param xType type of X
     * @param x statement number of X
     * @return true if Affects(X,_), false otherwise
     */
    bool affects_X_Y_int_X_smth(DesignEnt xType, int x) const;

    /**
     * Returns true if Affects(_,Y)
     * @param xType type of Y
     * @param x statement number of Y
     * @return true if Affects(_,Y), false otherwise
     */
    bool affects_X_Y_smth_int_Y(DesignEnt yType, int y) const;

    /**
     * Affects*(X,Y); given Y (int), retrieve all X (int) such that
     * Affects*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that Affects*(X,Y)
     */
    std::set<int> affectsStar_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;
    /**
     * Affects*(X,Y); given X (int), retrieve all Y (int) such that
     * Affects*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that Affects*(X,Y)
     */
    std::set<int> affectsStar_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;
    /**
     * Given X (int) and Y (int), checks if Affects*(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param yType type of Y
     * @param y value of Y
     * @return true if Affects*(X,Y), false otherwise
     */
    bool affectsStar_query_int_X_int_Y(DesignEnt xType,
            int x, DesignEnt yType, int y) const;

    /**
     * Returns true if Affects*(X,_)
     * @param xType type of X
     * @param x statement number of X
     * @return true if Affects*(X,_), false otherwise
     */
    bool affectsStar_X_Y_int_X_smth(DesignEnt xType, int x) const;

    /**
     * Returns true if Affects*(_,Y)
     * @param xType type of Y
     * @param x statement number of Y
     * @return true if Affects*(_,Y), false otherwise
     */
    bool affectsStar_X_Y_smth_int_Y(DesignEnt yType, int y) const;

    /**
     * AffectsBip(X,Y); given Y (int), retrieve all X (int) such that
     * AffectsBip(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that AffectsBip(X,Y)
     */
    std::set<int> affectsBip_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;
    /**
     * AffectsBip(X,Y); given X (int), retrieve all Y (int) such that
     * AffectsBip(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that AffectsBip(X,Y)
     */
    std::set<int> affectsBip_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;

    /**
     * Given X (int) and Y (int), checks if AffectsBip(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param yType type of Y
     * @param y value of Y
     * @return true if AffectsBip(X,Y), false otherwise
     */
    bool affectsBip_query_int_X_int_Y(DesignEnt xType,
            int x, DesignEnt yType, int y) const;

    /**
     * Returns true if AffectsBip(X,_)
     * @param xType type of X
     * @param x statement number of X
     * @return true if AffectsBip(X,_), false otherwise
     */
    bool affectsBip_X_Y_int_X_smth(DesignEnt xType, int x) const;

    /**
     * Returns true if AffectsBip(_,Y)
     * @param xType type of Y
     * @param x statement number of Y
     * @return true if AffectsBip(_,Y), false otherwise
     */
    bool affectsBip_X_Y_smth_int_Y(DesignEnt yType, int y) const;

    /**
     * AffectsBip*(X,Y); given Y (int), retrieve all X (int) such that
     * AffectsBip*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param y integer value of Y
     * @return set of X (int) such that AffectsBip*(X,Y)
     */
    std::set<int> affectsBipStar_X_Y_get_int_X_from_int_Y(DesignEnt xType,
            DesignEnt yType, int y) const;

    /**
     * AffectsBip*(X,Y); given X (int), retrieve all Y (int) such that
     * AffectsBip*(X,Y).
     * @param xType type of X
     * @param yType type of Y
     * @param x integer value of X
     * @return set of Y (int) such that AffectsBip*(X,Y)
     */
    std::set<int> affectsBipStar_X_Y_get_int_Y_from_int_X(DesignEnt xType,
            DesignEnt yType, int x) const;

    /**
     * Given X (int) and Y (int), checks if AffectsBip*(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param yType type of Y
     * @param y value of Y
     * @return true if AffectsBip*(X,Y), false otherwise
     */
    bool affectsBipStar_query_int_X_int_Y(DesignEnt xType,
            int x, DesignEnt yType, int y) const;

    /**
     * Returns true if AffectsBip*(X,_)
     * @param xType type of X
     * @param x statement number of X
     * @return true if AffectsBip*(X,_), false otherwise
     */
    bool affectsBipStar_X_Y_int_X_smth(DesignEnt xType, int x) const;

    /**
     * Returns true if AffectsBip*(_,Y)
     * @param xType type of Y
     * @param x statement number of Y
     * @return true if AffectsBip*(_,Y), false otherwise
     */
    bool affectsBipStar_X_Y_smth_int_Y(DesignEnt yType, int y) const;

    // Retrieve everything
    std::set<int> get_all_assign() const;
    std::set<int> get_all_if() const;
    std::set<int> get_all_while() const;
    std::set<int> get_all_call() const;
    std::set<int> get_all_stmt() const;
    std::set<int> get_all_progline() const;
    std::set<int> get_all_stmtLst() const;
    std::set<std::string> get_all_vars() const;
    std::set<std::string> get_all_procs() const;
    std::set<int> get_all_const() const;

    bool has_assign(int assign) const;
    bool has_call(int callStmt) const;
    /// Checks if any call statement calls a given procedure
    /// @procName the procedure to check for
    /// @return true if a call statement calls the given procedure,
    ///         false otherwise
    bool has_call_procName(const std::string& procName) const;
    bool has_if (int ifStmt) const;
    bool has_while(int whileStmt) const;
    bool has_stmt(int stmtNo) const;
    bool has_progline(int progLine) const;
    bool has_variable(const std::string& varName) const;
    bool has_procedure(const std::string& procName) const;
    bool has_const(int n) const;
    bool has_stmtLst(int stmtNo) const;

    /// Checks if there is at least one of a certain design
    /// entity present in the PKB
    /// @param entType type of the design entity
    /// @return true if at least one design entity of entType
    /// exists, false otherwise
    bool has_any_ent(DesignEnt entType) const;

    /// Checks if there is any call statement inside the
    /// PKB
    /// @return true if there is at least one call statement
    ///         inside the PKB, false otherwise
    bool has_any_call() const;
    /// Checks if Follows(_,_) / Follows*(_,_) is true
    /// NOTE: This is NOT thread-safe
    /// @return true if Follows(_,_) is true
    ///         [which implies Follows*(_,_) is true]
    bool has_any_follows();
    /// Checks if Next(_,_) / Next*(_,_) is true
    /// NOTE: This is NOT thread-safe
    /// @return true if Next(_,_) is true
    ///         [which implies Next*(_,_) is true]
    bool has_any_next();
    /// Checks if Affects(_,_) / Affects*(_,_) is true
    /// NOTE: This is NOT thread-safe
    /// @return true if Affects(_,_) is true
    ///         [which implies Affects*(_,_) is true]
    bool has_any_affects();
    /// Checks if NextBip(_,_) / NextBip*(_,_) is true
    /// NOTE: This is NOT thread-safe
    /// @return true if NextBip(_,_) is true
    ///         [which implies NextBip*(_,_) is true]
    bool has_any_nextBip();
    /// Checks if AffectsBip(_,_) / AffectsBip*(_,_) is true
    /// NOTE: This is NOT thread-safe
    /// @return true if AffectsBip(_,_) is true
    ///         [which implies AffectsBip*(_,_) is true]
    bool has_any_affectsBip();

    //////////////////////////////////////////////////////////////////
    // For pattern clause
    //////////////////////////////////////////////////////////////////
    /**
     * Returns the control variable of a given statement.
     * @param entType type of the statement
     * @param stmtNo statement number
     * @return control variable of the statement if appropriate,
     *         otherwise the empty string
     */
    const std::string& get_control_variable(DesignEnt entType,
            int stmtNo) const;

    /**
     * Checks if a given variable is the control variable of a stmt
     * @param entType type of the statement
     * @param stmtNo statement number
     * @param varName name of variable
     * @return true if the statement has a control variable named
     *         varName, false otherwise
     */
    bool has_control_variable(DesignEnt entType,
            int stmtNo, const std::string& varName) const;

    /**
     * Returns the procedure called by the call stmt, or an
     * empty string if the statement does not exist or is not
     * a call statement.
     * @param callStmt statement number of the call stmt
     * @return procedure called by callStmt if it is a proper
     *         call statement, the empty string otherwise
     */
    std::string get_call_procName(int callStmt) const;

    /**
     * Returns all call stmts that call a certain procedure.
     * @param proc name of procedure being called
     * @return set of integers of all the call statements calling
     *         procedure proc
     */
    std::set<int> get_call_stmt_calling(const std::string& proc) const;
    
    // Variables
    set<string> get_all_vars_by_proc(string procName);

    set<int> get_stmt_modifies(const std::string& var) const;
    
    set<string> get_var_stmt_modifies(int stmtNo) const;

    // Next BIP
    bool is_next_BIP(int stmt1, int stmt2) const;
    bool is_next_star_BIP(int stmt1, int stmt2) const;

    set<int> get_before_BIP(int stmtNo) const;
    set<int> get_before_BIP_star(int stmtNo) const;

    set<int> get_after_BIP(int stmtNo) const;
    set<int> get_after_BIP_star(int stmtNo) const;

    // Affects Bip
    bool is_affects_Bip(int stmt1, int stmt2) const;
    bool is_affects_star_Bip(int stmt1, int stmt2) const;

    set<int> get_affects_Bip(int stmtNo) const;
    set<int> get_affects_star_Bip(int stmtNo) const;

    set<int> get_affected_by_Bip(int stmtNo) const;
    set<int> get_affected_by_star_Bip(int stmtNo) const;

    // Others
    bool is_stmtType(int stmtNo, DesignEnt type) const;
    bool is_valid_stmtNo(int stmtNo) const;
    bool is_same_procedure(int stmt1, int stmt2) const;

    set<int> get_all_stmt();
    set<int> get_all_stmt_by_proc(string procName);

    set<int> filter_by_proc(string procName, const set<int>& s) const;
    set<int> filter_by_stmtType(DesignEnt type, set<int> s);
    int filter_by_stmtType(DesignEnt type, int stmtNo);

    // Debuggers
    Node* get_progRoot();
    ProcTable* get_procTable();
    StmtBank* get_stmtBank();
    VarTable* get_varTable();
    vector<CFGNode*>* get_CFG();
    set<int> visited;
    void dfs(CFGNode *node);

private:

    Node *progRoot;
    ProcTable *procTable;
    VarTable *varTable;
    StmtBank *stmtBank;
    vector<CFGNode*> *CFG;

    /*
     * Retrieves the Node representing the statement.
     * @param entType type of the statement
     * @param stmtNo statement number
     * @return A Node* representing the statement if there exists
     *         a statement of entType at stmtNo. Otherwise, returns
     *         NULL.
     */
    Node *get_stmt_node(DesignEnt entType, int stmtNo) const;

    static const std::string EMPTY_STRING;
    const set<string> EMPTY_STRINGSET;
    const set<int> EMPTY_INTSET;

    bool hasAnyFollowsComputed_;
    bool hasAnyFollowsVal_;
    bool hasAnyNextComputed_;
    bool hasAnyNextVal_;
    bool hasAnyAffectsComputed_;
    bool hasAnyAffectsVal_;
    bool hasAnyNextBipComputed_;
    bool hasAnyNextBipVal_;
    bool hasAnyAffectsBipComputed_;
    bool hasAnyAffectsBipVal_;
};

#endif