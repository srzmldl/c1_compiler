#include <stdio.h>
#include <string>
#include <bits/stdc++.h>
#include "node.hh"
#include "tok.hh"
// comment the next line to hide debug info
//#define DEBUG
#include "util.hh"
#include "global.hh"

extern FILE *yyin;      // flex uses yyin as input file's pointer
extern int yylex();     // lexer.cc provides yylex()
extern int yyparse();   // parser.cc provides yyparse()
extern InputNode *root; // AST's root, shared with yyparse()
extern std::vector <std::string> wholeFile;

int main(int argc, char** argv)
{
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

    dumpfp = fopen("c1.dot", "w");
    if (dumpfp != NULL) {
        DumpDOT *dumper = new DumpDOT(dumpfp);
        root->dumpdot(dumper);
        delete dumper;
        fclose(dumpfp);
    }
    /*root->printast(stdout, 0);*/
    return 0;
}
