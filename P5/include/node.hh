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
    VARDEFELEEQU,
    VARDEFARRLIMNOEQU,
    VARDEFELENOEQU,
    VARDEFARRLIMEQU,
    CONSTDECL,
    CONSTDEFARRNOLIM,
    MULTIEXPNODE,
    IDENT,
    CONSTDEFELE,
    INPUT,
    VARDECL,
    FUNCDEF,
    VARDEFARRNOLIMEQU,
    BINARYEXP,
    UNARYEXP,
    BLOCK,
    CONSTDEFARRLIM,
    ASSIGNSTMT,
    CALLSTMT,
    IFSTMTNODE,
    WHILESTMT,
    COMMASTMT,
    REFARRNODE,
    COND,
    IFELSESTMTNODE
} NodeType;

class Node {
    
public:
    NodeType type;
    //virtual //void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};

class ExpNode: public Node{
public:
    ExpNode *nextExp, *headExp;
    //virtual //void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};

class LValNode : public ExpNode {
public:
    //virtual //void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};

class InputNode : public Node {
    vector<Node*> comps;
public:
    InputNode() { type = INPUT; };
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    void append(Node *compUnit);
};

class  IdentNode : public Node {
public:
    std::string *name;
    IdentNode(std::string *name) : name(name) {
        type = IDENT;
    };
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

class NumNode : public ExpNode {
public:
    int val;
    NumNode(int val) : val(val) {
        type = NUM;
        nextExp = NULL;
        headExp = this;
    };
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

class BinaryExpNode : public ExpNode {
public:
    char op;
    ExpNode *lhs, *rhs;
    BinaryExpNode(ExpNode *lhs, char op, ExpNode *rhs) : op(op), lhs(lhs), rhs(rhs) {
        type = BINARYEXP;
        nextExp = NULL;
        headExp = this;
    };
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

class UnaryExpNode : public ExpNode {
public:
    char op;
    ExpNode *operand;
    UnaryExpNode(char op, ExpNode *operand) : op(op), operand(operand) {
        type = UNARYEXP;
        nextExp = NULL;
        headExp = this;
    };
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

//=================

class BlockItemNode : public Node {
public:
    BlockItemNode *next, *head;
    //virtual //void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};
    
class BlockNode : public Node {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    BlockItemNode *fir;
    BlockNode(BlockItemNode* fir) : fir(fir){
        type = BLOCK;
    };
};

//=========


class CondNode : public Node {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    ExpNode *lhs, *rhs;
    std::string *RelOp;
    CondNode(ExpNode *lhs, std::string *RelOp, ExpNode *rhs) : lhs(lhs), rhs(rhs), RelOp(RelOp) {
        type = COND;
    }
};

class DeclNode : public Node{
public:
    Node *next, *head;
    //virtual //void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};

class ConstDefNode : public Node {
public:
    ConstDefNode *constNext, *constHead;
    //virtual //void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};

class ConstDefEleNode : public ConstDefNode {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    ExpNode* exp;
    ConstDefEleNode(IdentNode* ident, ExpNode* exp) : ident(ident), exp(exp) {
        constNext = NULL;
        constHead = this;
        type = CONSTDEFELE;
    };
};

class ConstDefArrLimNode : public ConstDefNode {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    ExpNode* lim;
    ExpNode* fir;
    ConstDefArrLimNode(IdentNode* ident, ExpNode* lim, ExpNode* fir) : ident(ident), lim(lim), fir(fir) {
        type = CONSTDEFARRLIM;
        constNext = NULL;
        constHead = this;
    };
};
    
class ConstDefArrNoLimNode : public ConstDefNode {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    MultiExpNode* multiExp;

    ConstDefArrNoLimNode(IdentNode* ident, MultiExpNode* multiExp) : ident(ident), multiExp(multiExp) {
        type = CONSTDEFARRNOLIM;
        constNext = NULL;
        constHead = this;
    };
};
    
class ConstDeclNode : public DeclNode {
public:
    ConstDefNode* fir;
    ConstDeclNode(ConstDefNode* fir) : fir(fir) {
        type = CONSTDECL;
        next = NULL;
        head = this;
    };
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

class VarDefNode : public Node {
public:
    VarDefNode *varNext, *varHead;
    //virtual //void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};

//var -> ident
class VarDefEleNoEquNode : public VarDefNode {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;

    VarDefEleNoEquNode(IdentNode* ident) : ident(ident) {
        varNext = NULL;
        varHead = this;
        type = VARDEFELENOEQU;
    };
};

//var -> ident[exp]
class VarDefArrLimNoEquNode : public VarDefNode {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    ExpNode* lim;
    
    VarDefArrLimNoEquNode(IdentNode* ident, ExpNode* lim) : ident(ident), lim(lim) {
        type = VARDEFARRLIMNOEQU;
        varNext = NULL;
        varHead = this;
    };
};

//var -> ident = Exp
class VarDefEleEquNode : public VarDefNode {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    ExpNode* exp;
    
    VarDefEleEquNode(IdentNode* ident, ExpNode* exp) : ident(ident), exp(exp) {
        varNext = NULL;
m        type = VARDEFELEEQU;
        varHead = this;
    };
};

//var -> ident[] = {1, 2,3}
class VarDefArrNoLimEquNode : public VarDefNode{
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    MultiExpNode* multiExp;

    VarDefArrNoLimEquNode(IdentNode* ident, MultiExpNode* multiExp) : ident(ident), multiExp(multiExp) {
        type = VARDEFARRNOLIMEQU;
        varNext = NULL;
        varHead = this;
    };
};

//var -> ident[Exp] = {1, 2, 4}
class VarDefArrLimEquNode : public VarDefNode {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    ExpNode* lim;
    MultiExpNode* multiExp;

    VarDefArrLimEquNode(IdentNode* ident, ExpNode* lim, MultiExpNode* multiExp) : ident(ident), lim(lim), multiExp(multiExp) {
        type = VARDEFARRLIMEQU;
        varNext = NULL;
        varHead = this;
    };
};
    
class VarDeclNode : public DeclNode {
public:
    VarDefNode* fir;
    VarDeclNode(VarDefNode* fir) : fir(fir) {
        type = VARDECL;
        next = NULL;
        head = this;
        };
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

//======================

//=============================================
class FuncDefNode : public Node{
public:
    Node *next, *head;
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    BlockNode* block;
    FuncDefNode(IdentNode* ident, BlockNode* block) : ident(ident), block(block) {
        next = NULL;
        head = this;
        type = FUNCDEF;
    };
    
};


class StmtNode : public BlockItemNode {
public:
    //virtual //void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};

//stmt -> LVal = exp;
class AssignStmtNode : public StmtNode {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    LValNode* LVal;
    ExpNode* exp;
    AssignStmtNode(LValNode *LVal, ExpNode *exp): LVal(LVal), exp(exp) {
        type = ASSIGNSTMT;
        next = NULL;
        head = this;
    }
};

//stmt -> ident();
class CallStmtNode : public StmtNode {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    CallStmtNode(IdentNode* ident) : ident(ident) {
        type = CALLSTMT;
        next = NULL;
        head = this;
    }
};
//stmt -> Block

//stmt -> if (Cond) Stmt
class IfStmtNode : public StmtNode {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    CondNode* cond;
    StmtNode* stmt;
    IfStmtNode(CondNode* cond, StmtNode* stmt) : cond(cond), stmt(stmt) {
        type = IFSTMTNODE;
        next = NULL;
        head = this;
    }
};

//stmt -> if (Cond) stmt else stmt
class IfElseStmtNode : public StmtNode {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    CondNode *cond;
    StmtNode *thenStmt, *elseStmt;
    IfElseStmtNode(CondNode* cond, StmtNode* thenStmt, StmtNode* elseStmt) : cond(cond), thenStmt(thenStmt), elseStmt(elseStmt) {
        type = IFELSESTMTNODE;
        next = NULL;
        head = this;
    }
};

//stmt -> while(Cond) Stmt
class WhileStmtNode : public StmtNode {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    CondNode* cond;
    StmtNode* stmt;
    WhileStmtNode(CondNode* cond, StmtNode* stmt) : cond(cond), stmt(stmt) {
        type = WHILESTMT;
        next = NULL;
        head = this;
    }
};
//stmt -> ;
class CommaStmtNode : public StmtNode {
    
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    CommaStmtNode() {
        type = COMMASTMT;
        next = NULL;
        head = this;
    }
};

//LVal --> ident [Exp]
class RefArrNode : public LValNode {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode *ident;
    ExpNode *exp;
    RefArrNode(IdentNode *ident, ExpNode *exp) : ident(ident), exp(exp) {
        type = REFARRNODE;
        nextExp = NULL;
        headExp = this;
    }
};
    
    
#endif
