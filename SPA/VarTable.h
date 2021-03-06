#ifndef T11_TABLES_AST_H
#define T11_TABLES_AST_H

#include <vector>
#include <string>
#include <map>
#include <set>
#include "PQL.h"

using std::vector;
using std::pair;
using std::string;
using std::set;

/// An entry inside the varTable
struct VarElements {
    int index;
    string var;

    std::set<int> assignModifying;
    std::set<int> ifModifying;
    std::set<int> whileModifying;
    std::set<int> callModifying;
    std::set<int> stmtModifying;
    std::set<int> usedBy;

    std::set<std::string> procModifying;

    std::set<int> assignUsing;
    std::set<int> ifUsing;
    std::set<int> whileUsing;
    std::set<int> callUsing;
    std::set<int> stmtUsing;
    set<string> usedByProc;

    VarElements();
    VarElements(int id, string name);
    VarElements(const struct VarElements &other);
    VarElements& operator=(const struct VarElements &other);
};

/// Stores information relating to variables
class VarTable {
public:
    VarTable();
    VarTable(const VarTable &other);
    VarTable& operator=(const VarTable &other);
    ~VarTable();

    int get_index(string var) const;
    const std::string& get_var_name(int index) const;

    int insert_var(string var);

    void add_assign_modifies_var(int assign, const std::string& var);
    void add_if_modifies_var(int ifStmt, const std::string& var);
    void add_while_modifies_var(int whileStmt, const std::string& var);
    void add_call_modifies_var(int callStmt, const std::string& var);
    void add_stmt_modifies_var(int stmtNo, const std::string& var);
    void add_proc_modifies_var(const std::string& procName,
            const std::string &var);
    void add_used_by(string var, DesignEnt entType, int stmtNo);
    void add_used_by(string var, DesignEnt entType, string procName);

    const set<int>& get_assign_modifying_var(const std::string& var) const;
    const set<int>& get_if_modifying_var(const std::string& var) const;
    const set<int>& get_while_modifying_var(const std::string& var) const;
    const set<int>& get_call_modifying_var(const std::string& var) const;
    const set<int>& get_stmt_modifying_var(const std::string& var) const;
    const std::set<std::string>&
        get_all_procedures_modifying(const std::string& var) const;
    const set<int>& get_modified_by(int index) const;
    const set<int>& get_used_by(string var) const;
    const set<int>& get_used_by(int index) const;

    /*
     * Given X (int) and Y (variable), checks if Uses(X,Y) is true.
     * @param xType type of X
     * @param x value of X
     * @param var value of variable Y
     * @return true if Uses(X,Y), false otherwise
     */
    bool uses_query_int_X_var(DesignEnt xType, int x,
            const std::string& var) const;

    const std::set<int>& get_X_using_var(DesignEnt entType,
            const std::string& var) const;
    const std::set<std::string>& get_string_X_using_var(
            DesignEnt entType, const std::string& var) const;

    const std::set<std::string>& get_all_vars() const;

    /// Checks if the VarTable contains any variable
    /// @returns true if there is at least one variable in the
    ///          VarTable, false otherwise
    bool has_any_var() const;

    /// Checks if anything uses a given variable
    /// @param varName the name of the variable
    /// @return true if the given variable is used somewhere,
    ///         false otherwise
    bool anyone_uses_this_var(const std::string& varName) const;

private:
    const set<int> EMPTY_INTSET;
    const set<string> EMPTY_STRINGSET;
    vector<VarElements> varTable;
    std::set<std::string> varSet_;
    std::map<string,int> nameToIndex;
};

#endif