#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <map>
#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include "node.hh"
#include "dumpdot.hh"
#include <iostream>

//===----------------------------------------------------------------------===//
// Utilities in Dump DOT
//===----------------------------------------------------------------------===//

// There are two ways to create a dot node:
// 1. newNode(num, str1, str2, ...)
//    num corresponds to the number of strings
//    Each string will appear in the generated image as a port
//    All strings are char*
// 2. newNode(vec)
//    All elements of the vector are std::string
// newNode returns an integer, which is the number of the corresponding
// node in DOT file.

int DumpDOT::newNode(int num, ...) {
    va_list list;
    va_start(list, num);
    fprintf(fp, "    %d [label = \"", count);
    bool first = true;
    for (int i=0; i<num; i++) {
        char* st = va_arg(list, char*);
        if (!first)
            fprintf(fp, "|");
        first = false;
        if (st[0] == '<' || st[0] == '>')
            fprintf(fp, "<%d> \\%s", i, st);
        else
            fprintf(fp, "<%d> %s", i, st);
    }
    va_end(list);
    fprintf(fp, "\"];\n");
    return count++;
}

int DumpDOT::newNode(std::vector<std::string> list) {
    fprintf(fp, "    %d [label = \"", count);
    bool first = true;
    for (int i=0; i<list.size(); i++) {
        std::string st = list[i];
        if (!first)
            fprintf(fp, "|");
        first = false;
        fprintf(fp, "<%d> %s", i, st.c_str());
    }
    fprintf(fp, "\"];\n");
    return count++;
}

// Draw a line from nSrc node's pSrc port to nDst node.
// If you want it start from the whole node, let pSrc = -1

void DumpDOT::drawLine(int nSrc, int pSrc, int nDst) {
    fprintf(fp, "    %d", nSrc);
    if (pSrc>=0)
        fprintf(fp, ":%d", pSrc);
    fprintf(fp, " -> %d;\n", nDst);
}

void drawList(int nThis, int pos, Node *list, DumpDOT *dumper) {
    for (Node *tmp = list; tmp; tmp = tmp->next) {
        int ntmp = tmp->dumpdot(dumper);
        dumper->drawLine(nThis, pos, ntmp);
    }
}
//===----------------------------------------------------------------------===//
// Dump AST to DOT
//===----------------------------------------------------------------------===//

// The following functions convert AST to DOT using DumpDOT.
// Each dumpdot returns an integer, which is corresponding number in DOT file.
// 53+29*71 will become:
// digraph {
// node [shape = record];
//     0 [label = "<0> |<1> +|<2> "];
//     1 [label = "<0> 53"];
//     2 [label = "<0> |<1> *|<2> "];
//     3 [label = "<0> 29"];
//     4 [label = "<0> 71"];
//     0:0 -> 1;
//     0:2 -> 2;
//     2:0 -> 3;
//     2:2 -> 4;
// }


int InputNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << comps.size() << " compUnits";
    int nThis = dumper->newNode(1, strs.str().c_str());
    for (Node* comp : comps) {
        //std::cout << comp->type << "!!!" << endl;
        int ncomp = comp->dumpdot(dumper);
        dumper->drawLine(nThis, 0, ncomp);
    }
    return nThis;
}

int IdentNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(1, name->c_str());
    return nThis;
}

int NumNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    strs << val;
    int nThis = dumper->newNode(1, strs.str().c_str());
    return nThis;
}

int BinaryExpNode::dumpdot(DumpDOT *dumper) {
    char st[2] = " ";
    st[0] = op;
    int nThis = dumper->newNode(3, " ", st, " ");
    int nlhs = lhs->dumpdot(dumper);
    int nrhs = rhs->dumpdot(dumper);
    dumper->drawLine(nThis, 0, nlhs);
    dumper->drawLine(nThis, 2, nrhs);
    return nThis;
}

int UnaryExpNode::dumpdot(DumpDOT *dumper) {
    char st[2] = " ";
    st[0] = op;
    int nThis = dumper->newNode(2, st, " ");
    int nOperand = operand->dumpdot(dumper);
    dumper->drawLine(nThis, 1, nOperand);
    return nThis;
}

int BlockNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(1, "\\{blocks\\}");
    drawList(nThis, 0, blockList, dumper);
    return nThis;
}

int CondNode::dumpdot(DumpDOT *dumper) {
    std::ostringstream strs;
    int nThis = dumper->newNode(3, " ", RelOp->c_str(), " ");
    int nlhs = lhs->dumpdot(dumper);
    int nrhs = rhs->dumpdot(dumper);
    dumper->drawLine(nThis, 0, nlhs);
    dumper->drawLine(nThis, 2, nrhs);
    return nThis;
}

int ConstDefEleNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(3, "ident", "=", "exp");
    int nident = ident->dumpdot(dumper);
    int nexp = exp->dumpdot(dumper);
    dumper->drawLine(nThis, 0, nident);
    dumper->drawLine(nThis, 2, nexp);
    return nThis;
}

int ConstDefArrLimNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(4, "ident", "\\[lim\\]", "=", "\\{Exps\\}");
    int nident = ident->dumpdot(dumper);
    int nlim = lim->dumpdot(dumper);
    dumper->drawLine(nThis, 0, nident);
    dumper->drawLine(nThis, 1, nlim);
    drawList(nThis, 3, expLink, dumper);
    return nThis;
}

int ConstDefArrNoLimNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(3, "ident", "\\[\\]=", "\\{exps\\}");
    int nident = ident->dumpdot(dumper);
    dumper->drawLine(nThis, 0, nident);
    drawList(nThis, 2, expLink, dumper);
    return nThis;
}

int ConstDeclNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(1, "Const");
    drawList(nThis, 0, constDefLink, dumper);
    return nThis;
}

int VarDefEleNoEquNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(1, ident->name->c_str());
    return nThis;
}

int VarDefArrLimNoEquNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(2, "ident", "\\[lim\\]");
    int nident = ident->dumpdot(dumper);
    int nlim = lim->dumpdot(dumper);
    dumper->drawLine(nThis, 0, nident);
    dumper->drawLine(nThis, 1, nlim);
    return nThis;
}

int VarDefEleEquNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(3, "ident", "=", "exp");
    int nident = ident->dumpdot(dumper);
    int nexp = exp->dumpdot(dumper);
    dumper->drawLine(nThis, 0, nident);
    dumper->drawLine(nThis, 2, nexp);
    return nThis;
}

int VarDefArrNoLimEquNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(3, "ident\\[\\]", "= ", "\\{exps\\}");
    int nident = ident->dumpdot(dumper);
    dumper->drawLine(nThis, 0, nident);
    drawList(nThis, 2, expList, dumper);
    return nThis;
}

int VarDefArrLimEquNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(4, "ident", "\\[lim\\]", "=", "\\{exps\\}");
    int nident = ident->dumpdot(dumper);
    int nlim = lim->dumpdot(dumper);
    dumper->drawLine(nThis, 0, nident);
    dumper->drawLine(nThis, 1, nlim);
    drawList(nThis, 3, expList, dumper);
    return nThis;
}

int VarDeclNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(1, "Var");
    drawList(nThis, 0, varDefList, dumper);
    return nThis;
}

int FuncDefNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(2, "Ident\\(\\)", "funcBlock");
    int nident = ident->dumpdot(dumper);
    int nblock = block->dumpdot(dumper);
    dumper->drawLine(nThis, 0, nident);
    dumper->drawLine(nThis, 1, nblock);
    return nThis;
}

int AssignStmtNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(3, "LVal", "=", "exp");
    int nlval = LVal->dumpdot(dumper);
    int nexp = exp->dumpdot(dumper);
    dumper->drawLine(nThis, 0, nlval);
    dumper->drawLine(nThis, 2, nexp);
    return nThis;
}

int CallStmtNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(1, "ident\\(\\)");
    int nident = ident->dumpdot(dumper);
    dumper->drawLine(nThis, 0, nident);
    return nThis;
}

int IfStmtNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(3, "if", "cond", "then");
    int ncond = cond->dumpdot(dumper);
    int nstmt = stmt->dumpdot(dumper);
    dumper->drawLine(nThis, 1, ncond);
    dumper->drawLine(nThis, 2, nstmt);
    return nThis;
}

int IfElseStmtNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(4, "if", "cond", "then", "else");
    int ncond = cond->dumpdot(dumper);
    int nthen = thenStmt->dumpdot(dumper);
    int nelse = elseStmt->dumpdot(dumper);
    dumper->drawLine(nThis, 1, ncond);
    dumper->drawLine(nThis, 2, nthen);
    dumper->drawLine(nThis, 3, nelse);
    return nThis;
}

int WhileStmtNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(3, "while", "cond", "stmt");
    int ncond = cond->dumpdot(dumper);
    int nstmt = stmt->dumpdot(dumper);
    dumper->drawLine(nThis, 1, ncond);
    dumper->drawLine(nThis, 2, nstmt);
    return nThis;
}

int CommaStmtNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(1, "\\;");
    return nThis;
}

int RefArrNode::dumpdot(DumpDOT *dumper) {
    int nThis = dumper->newNode(2, "ident", "\\[exp\\]");
    int nident = ident->dumpdot(dumper);
    int nexp = exp->dumpdot(dumper);
    dumper->drawLine(nThis, 0, nident);
    dumper->drawLine(nThis, 1, nexp);
    return nThis;
}


