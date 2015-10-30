#ifndef _NODE_HH_
#define _NODE_HH_

#include <stdio.h>
#include <string>
#include <vector>
#include "dumpdot.hh"
using namespace std;

typedef enum
{
    NUM,
    VAR,
    INPUT,
    LINE,
    ASGN,
    EXP,
    BINARYEXP,
    UNARYEXP
} NodeType;

class Node {
public:
    NodeType type;
    virtual void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};

class ExpNode : public Node {
public:
    virtual void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};

class NumNode : public ExpNode {
    int val;
public:
    NumNode(int val) : val(val) { type = EXP; };
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

class VarNode : public ExpNode {
    std::string *name;
public:
    VarNode(std::string* name) : name(name) { type = VAR; };
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

class BinaryExpNode : public ExpNode {
    char op;
    ExpNode *lhs, *rhs;
public:
    BinaryExpNode(char op, ExpNode *lhs, ExpNode *rhs) : op(op), lhs(lhs), rhs(rhs) { type = BINARYEXP; };
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

class UnaryExpNode : public ExpNode {
    char op;
    ExpNode *operand;
public:
    UnaryExpNode(char op, ExpNode *operand) : op(op), operand(operand) { type = UNARYEXP; };
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

class AsgnNode : public Node {
    VarNode *var;
    ExpNode *exp;
public:
    AsgnNode(VarNode *var, ExpNode *exp) : var(var), exp(exp) { type = ASGN; };
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

class LineNode : public Node {
    AsgnNode *asgn;
public:
    LineNode(AsgnNode *asgn) : asgn(asgn) { type = LINE; };
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

class InputNode : public Node {
    vector<LineNode*> lines;
public:
    InputNode() { type = INPUT; };
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    void append(LineNode *line);
};

#endif
