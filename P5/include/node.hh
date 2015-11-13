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

typedef struct {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
} Loc;

class Node {
public:
    NodeType type;
    Node *head, *next; //own link
    Loc* loc;
    Node() {loc = (Loc*)malloc(sizeof(Loc));}
    void setLoc(Loc* loc);
    //virtual //void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
    virtual ~Node() {};
};

class InputNode : public Node {
    vector<Node*> comps;
public:
    InputNode() {
        type = INPUT;
        head = this;
        next = NULL;
    };
    //~InputNode() {};
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    void append(Node *compUnit);
};

class  IdentNode : public Node {
public:
    std::string *name;
    IdentNode(std::string *name) : name(name) {
        next = NULL;
        head = this;
        type = IDENT;
    };
    //~IdentNode(){};
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

class NumNode : public Node {
public:
    int val;
    NumNode(int val) : val(val) {
        type = NUM;
        head = this;
        next = NULL;
    };
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

class BinaryExpNode : public Node {
public:
    char op;
    Node *lhs, *rhs;
    BinaryExpNode(Node *lhs, char op, Node *rhs) : op(op), lhs(lhs), rhs(rhs) {
        type = BINARYEXP;
        next = NULL;
        head = this;
    };
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

class UnaryExpNode : public Node {
public:
    char op;
    Node *operand;
    UnaryExpNode(char op, Node *operand) : op(op), operand(operand) {
        type = UNARYEXP;
        next = NULL;
        head = this;
    };
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

//=================
    
class BlockNode : public Node {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    Node *blockList;
    BlockNode(Node* blockList) : blockList(blockList){
        type = BLOCK;
        next = NULL;
        head = this;
    };
};

//=========
class CondNode : public Node {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    Node *lhs, *rhs;
    std::string *RelOp;
    CondNode(Node *lhs, std::string *RelOp, Node *rhs) : lhs(lhs), rhs(rhs), RelOp(RelOp) {
        type = COND;
        next = NULL;
        head = this;
    }
};

class ConstDefEleNode : public Node {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode *ident;
    Node *exp;
    ConstDefEleNode(IdentNode *ident, Node *exp) : ident(ident), exp(exp) {
        next = NULL;
        head = this;
        type = CONSTDEFELE;
    };
};

class ConstDefArrLimNode : public Node {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    Node* lim;
    Node* expLink;
    ConstDefArrLimNode(IdentNode* ident, Node* lim, Node* expLink) : ident(ident), lim(lim), expLink(expLink) {
        type = CONSTDEFARRLIM;
        next = NULL;
        head = this;
    };
};
    
class ConstDefArrNoLimNode : public Node {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    Node* expLink;

    ConstDefArrNoLimNode(IdentNode* ident, Node* expLink) : ident(ident), expLink(expLink) {
        type = CONSTDEFARRNOLIM;
        next = NULL;
        head = this;
    };
};
    
class ConstDeclNode : public Node {
public:
    Node *constDefLink;
    ConstDeclNode(Node* constDefLink) : constDefLink(constDefLink) {
        type = CONSTDECL;
        next = NULL;
        head = this;
    };
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
};

//var -> ident
class VarDefEleNoEquNode : public Node {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;

    VarDefEleNoEquNode(IdentNode* ident) : ident(ident) {
        next = NULL;
        head = this;
        type = VARDEFELENOEQU;
    };
};

//var -> ident[exp]
class VarDefArrLimNoEquNode : public Node {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode *ident;
    Node *lim;
    
    VarDefArrLimNoEquNode(IdentNode *ident, Node *lim) : ident(ident), lim(lim) {
        type = VARDEFARRLIMNOEQU;
        next = NULL;
        head = this;
    };
};

//var -> ident = Exp
class VarDefEleEquNode : public Node {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode *ident;
    Node *exp;
    
    VarDefEleEquNode(IdentNode* ident, Node* exp) : ident(ident), exp(exp) {
        next = NULL;
        type = VARDEFELEEQU;
        head = this;
    };
};

//var -> ident[] = {1, 2,3}
class VarDefArrNoLimEquNode : public Node{
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode *ident;
    Node *expList;

    VarDefArrNoLimEquNode(IdentNode *ident, Node *expList) : ident(ident), expList(expList) {
        type = VARDEFARRNOLIMEQU;
        next = NULL;
        head = this;
    };
};

//var -> ident[Exp] = {1, 2, 4}
class VarDefArrLimEquNode : public Node {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode* ident;
    Node* lim;
    Node* expList;
    VarDefArrLimEquNode(IdentNode* ident, Node* lim, Node* expList) : ident(ident), lim(lim), expList(expList) {
        type = VARDEFARRLIMEQU;
        next = NULL;
        head = this;
    };
};
    
class VarDeclNode : public Node {
public:
    Node* varDefList;
    VarDeclNode(Node* varDefList) : varDefList(varDefList) {
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


class StmtNode : public Node {
public:
    //virtual //void printast(FILE *fp, int indent) = 0;
    virtual int dumpdot(DumpDOT *dumper) = 0;
};

//stmt -> LVal = exp;
class AssignStmtNode : public Node {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    Node *LVal;
    Node *exp;
    AssignStmtNode(Node *LVal, Node *exp): LVal(LVal), exp(exp) {
        type = ASSIGNSTMT;
        next = NULL;
        head = this;
    }
};

//stmt -> ident();
class CallStmtNode : public Node {
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
class IfStmtNode : public Node {
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
class IfElseStmtNode : public Node {
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
class WhileStmtNode : public Node {
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
class CommaStmtNode : public Node {
    
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
class RefArrNode : public Node {
public:
    //void printast(FILE *fp, int indent);
    int dumpdot(DumpDOT *dumper);
    IdentNode *ident;
    Node *exp;
    RefArrNode(IdentNode *ident, Node *exp) : ident(ident), exp(exp) {
        type = REFARRNODE;
        next = NULL;
        head = this;
    }
};
    
    
#endif
