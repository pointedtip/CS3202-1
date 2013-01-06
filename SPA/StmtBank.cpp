#include "StmtBank.h"

StmtBank::StmtBank(void)
{
}


StmtBank::~StmtBank(void)
{
}

void StmtBank::add_node_entry(int stmtNo, stmtType type, Node* node)
{
    directory[stmtNo] = type;
    switch(type) {
    case CALLTYPE:
        callBank[stmtNo] = node;
        break;
    case WHILETYPE:
        whileBank[stmtNo] = node;
        break;
    case IFTYPE:
        ifBank[stmtNo] = node;
        break;
    case ASSIGNTYPE:
        assignBank[stmtNo] = node;
        break;
    }
}

void StmtBank::add_constant(string n)
{
    constBank.insert(n);
}


map<int, stmtType> StmtBank::get_directory()
{
    return directory;
}

map<int, Node*> StmtBank::get_callBank()
{
    return callBank;
}

map<int, Node*> StmtBank::get_assignBank()
{
    return assignBank;
}

map<int, Node*> StmtBank::get_whileBank()
{
    return whileBank;
}

map<int, Node*> StmtBank::get_ifBank()
{
    return ifBank;
}

set<string> StmtBank::get_constBank()
{
    return constBank;
}

bool StmtBank::is_stmt_type(int stmtNo, stmtType type)
{
    if (directory.find(stmtNo) != directory.end()) {
        return (directory[stmtNo] == type);
    } else {
        return false;
    }
}

Node* StmtBank::get_node(int stmtNo)
{
    if (directory.find(stmtNo) != directory.end()) {
        stmtType type = directory[stmtNo];
        switch(type) {
        case CALLTYPE:
            return callBank[stmtNo];
            break;
        case WHILETYPE:
            return whileBank[stmtNo];
            break;
        case IFTYPE:
            return ifBank[stmtNo];
            break;
        case ASSIGNTYPE:
            return assignBank[stmtNo];
            break;
        }
    } else {
        return NULL;
    }
}