// comment the next line to hide debug info
//#define DEBUG
#include <stdio.h>
#include <string>
#include <bits/stdc++.h>
#include "node.hh"
#include "tok.hh"
#include "util.hh"
#include "global.hh"

using namespace llvm;

extern FILE *yyin;      // flex uses yyin as input file's pointer
extern int yylex();     // lexer.cc provides yylex()
extern int yyparse();   // parser.cc provides yyparse()
extern InputNode *root; // AST's root, shared with yyparse()
extern std::vector <std::string> wholeFile;
extern std::vector <Node*> nodeVec;
extern int errorFlag;

void generatellvmIR() {
    freopen("c1.ll", "w", stderr);
    root->Codegen();
}

int main(int argc, char** argv)
{
    errorFlag = 0;
    if (handle_opt(argc, argv) == false)
        return 0;
    freopen(argv[1], "r", stdin);
    std::string tmp;
    wholeFile.clear();
    for (; std::getline(std::cin, tmp); ) {
        wholeFile.push_back(tmp);
    }
    yyin = infp;        // infp is initialized in handle_opt()
    yyparse();
    fclose(stdin);
     //cout << root->type << endl;
    if (!errorFlag && root != NULL) {
        dumpfp = fopen("c1.dot", "w");
        if (dumpfp != NULL) {
            DumpDOT *dumper = new DumpDOT(dumpfp);
            root->dumpdot(dumper);
            delete dumper;
            fclose(dumpfp);
        }
    } else root = NULL;

    //cout << root->head->head << endl;
    /*root->printast(stdout, 0);*/

    if (!errorFlag && root != NULL) {
        //llvmirfp = fopen("c1.ll", "w");
        //if (llvmirfp != NULL) {
        generatellvmIR();
            //}
    } else root = NULL;

    return 0;
}
