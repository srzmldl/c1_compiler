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


class InputNode : public Node {
    vector<Node*> comp;
public:
    InputNode() { type = INPUT; };
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    void append(LineNode *line);
};

class DeclNode : public Node{
public:
    Node* next;
    virtual void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};

class ConstDefNode : public Node {
public:
    ConstDefNode* constNext;
    virtual void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};

class ConstDefEleNode : public ConstDefNode {
public:
    void printast(FILE *fp, int indent);
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
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    ExpNode* Lim;
    MultiExpNode* multiExp;
    
    ConstDefArrLimNode(IdentNode* ident, ExpNode* lim, MultiExpNode* multiExp) : ident(ident), lim(lim), multiExp(multiExp) {
        type = CONSTDEFARRLIM;
        constNext = NULL;
    };
}
    
class ConstDefArrNoLimNode : public ConstDefNode {
public:
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    MultiExpNode* multiExp;

    ConstDefArrNoLimNode(IdentNode* ident, MultiExpNode* multiExp) : ident(ident), multiExp(multiExp) {
        type = CONSTDEFARRNOLIM;
        constNext = NULL;
    };
}
    
class ConstDeclNode : public DeclNode {
public:
    ConstDefNode* fir;
    ConstDeclNode(ConstDefNode* fir) : fir(fir) {
        type = CONSTDECL;
        next = NULL;
    };
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

class VarDefNode : public Node {
public:
    VarDefNode* varNext;
    virtual void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};

//var -> ident
class VarDefEleNoEquNode : public VarDefNode {
public:
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;

    VarDefEleNode(IdentNode* ident) : ident(ident) {
        varNext = NULL;
        type = VARDEFELENOEQU;
    };
};

//var -> ident[exp]
class VarDefArrLimNoEquNode : public VarDefNode {
public:
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    ExpNode* lim;
    
    VarDefArrLimNoEquNode(IdentNode* ident, ExpNode* lim) : ident(ident), lim(lim) {
        type = VARDEFARRLIMNOEQU;
        varNext = NULL;
    };
}

//var -> ident = Exp
class VarDefEleEquNode : public VarDefNode {
public:
    void printast(FILE *fp, int indent);
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
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    MultiExpNode* multiExp;

    VarDefArrNoLimNode(IdentNode* ident, MultiExpNode* multiExp) : ident(ident), multiExp(multiExp) {
        type = VARDEFARRNOLIMEQU;
        varNext = NULL;
    };
}

//var -> ident[Exp] = {1, 2, 4}
class VarDefArrLimEquNode : public VarDefNode {
public:
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    ExpNode* lim;
    MultiExpNode* multiExp;

    VarDefArrNoLimNode(IdentNode* ident, ExpNode* lim, MultiExpNode* multiExp) : ident(ident), lim(lim), multiExp(multiExp) {
        type = VARDEFARRLIMEQU;
        varNext = NULL;
    };
}
    
class VarDeclNode : public DeclNode {
public:
    VarDefNode* fir;
    VarDeclNode(VarDefNode* fir) : fir(fir) {
        type = VARDECL
        next = NULL;
        };
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

//======================
class MultiExpNode: public Node {
    ExpNode* fir;
    MultiExpNode(ExpNode* fir) : fir(fir) {type = MULTIEXPNODE};
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

class ExpNode: public Node{
public:
    ExpNode* nextExp;
    virtual void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};

class BinaryExpNode : public ExpNode {
public: 
}

//=============================================
class FuncDefNode : public Node{
public:
    Node* next;
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    BlockNode* block;
    FuncDefNode(IdentNode* ident, BlockNode* block) : ident(ident), block(block) {
        next = NULL;
        type = FUNCDEF;
    };
    
};

class BlockItemNode : public Node {
public:
    Node* next;
    virtual void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};
    
class BlockNode : public Node {
public:
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    BlockItemNode* fir;
    FuncDefNode(BlockItemNode* fir) : fir(fir) {
        type = BLOCK;
    };
};

class StmtNode : public BlockItemNode {
public:
    virtual void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};

//stmt -> LVal = exp;
class AssignStmtNode : public StmtNode {
public:
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    LValNode* LVal;
    ExpNode* exp;
    AssignStmtNode((LValNode*) LVal, (ExpNode*) exp): LVal(LVal), exp(exp) {
        type = ASSIGNSTMT;
        next = NULL;
    }
};

//stmt -> ident();
class CallStmtNode : public StmtNode {
public:
    void printast(FILE *fp, int indent);
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
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    CondNode* cond;
    StmtNode* stmt;
    CallStmtNode(CondNode* cond, StmtNode* stmt) : cond(cond), stmt(stmt) {
        type = IfSTMTNODE;
        next = NULL;
    }
};

//stmt -> if (Cond) stmt else stmt
class IfElseStmtNode : public StmtNode {
public:
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    CondNode *cond;
    StmtNode *thenStmt, *elseStmt;
    CallStmtNode(CondNode* cond, StmtNode* thenStmt, StmtNode* elseStmt) : cond(cond), thenStmt(thenStmt), elseStmt(elseStmt) {
        type = IfSTMTNODE;
        next = NULL;
    }
};

//stmt -> while(Cond) Stmt
class WhileStmtNode : public StmtNode {
public:
    void printast(FILE *fp, int indent);
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
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    CommaStmtNode() {
        type = COMMASTMT;
        next = NULL;
    }
};


class LValNode : public Node {
public:
    virtual void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};

//LVal --> ident [Exp]
class RefArrNode : public LValNode {
public:
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode *ident;
    ExpNode *exp;
    RefArrNode(IdentNode *ident, ExpNode *exp) : ident(ident), exp(exp) {
        type = REFARRNODE;
    }
}
    
class CondNode : public Node {
public:
    void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    ExpNode *lhs, *rhs;
    std::string *RelOp;
    CondNode(ExpNode *lhs, std::string *RelOp, Expnode *rhs) : lhs(lhs), rhs(rhs), RelOp(RelOp) {
        type = COND;
    }
}





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


#endif
