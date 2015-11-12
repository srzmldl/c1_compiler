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
    ExpNode* nextExp;
    //virtual //void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};


class LValNode : public Node {
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
    NumNode(int val) : val(val) { type = NUM; };
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

class MultiExpNode: public Node {
public:
    ExpNode* fir;
    MultiExpNode(ExpNode* fir) : fir(fir) {type = MULTIEXPNODE;};
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
    };
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

class UnaryExpNode : public ExpNode {
public:
    char op;
    ExpNode *operand;
    UnaryExpNode(char op, ExpNode *operand) : op(op), operand(operand) { type = UNARYEXP; };
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

//=================

class BlockItemNode : public Node {
public:
    BlockItemNode* next;
    //virtual //void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};
    
class BlockNode : public Node {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    BlockItemNode* fir;
    BlockNode(BlockItemNode* fir) : fir(fir) {
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
    Node* next;
    //virtual //void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};

class ConstDefNode : public Node {
public:
    ConstDefNode* constNext;
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
        type = CONSTDEFELE;
    };
};

class ConstDefArrLimNode : public ConstDefNode {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    ExpNode* lim;
    MultiExpNode* multiExp;
    ConstDefArrLimNode(IdentNode* ident, ExpNode* lim, MultiExpNode* multiExp) : ident(ident), lim(lim), multiExp(multiExp) {
        type = CONSTDEFARRLIM;
        constNext = NULL;
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
    };
};
    
class ConstDeclNode : public DeclNode {
public:
    ConstDefNode* fir;
    ConstDeclNode(ConstDefNode* fir) : fir(fir) {
        type = CONSTDECL;
        next = NULL;
    };
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

class VarDefNode : public Node {
public:
    VarDefNode* varNext;
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
        type = VARDEFELEEQU;
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
    };
};
    
class VarDeclNode : public DeclNode {
public:
    VarDefNode* fir;
    VarDeclNode(VarDefNode* fir) : fir(fir) {
        type = VARDECL;
        next = NULL;
        };
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

//======================

//=============================================
class FuncDefNode : public Node{
public:
    Node* next;
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    BlockNode* block;
    FuncDefNode(IdentNode* ident, BlockNode* block) : ident(ident), block(block) {
        next = NULL;
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
    }
};
    
    
#endif
