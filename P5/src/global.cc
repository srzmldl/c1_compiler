#include <stdio.h>
#include <bits/stdc++.h>
#include "global.hh"
#include "node.hh"

char *infile_name = NULL;   // input file's name
char *outfile_name = NULL;  // output file's name
char *dumpfile_name = NULL; // dump file's name
FILE *infp = NULL;          // input file's pointer, default is stdin
FILE *outfp = NULL;         // output file's pointer, default is stdout
FILE *dumpfp = NULL;        // dump file's pointer
std::vector < std::string > wholeFile;
std::vector <Node*> nodeVec;
int errorFlag = 0;
//extern Node* root;

void clearNode() {
    //std::cout << nodeVec.size() << endl;
    for (; !nodeVec.empty(); ) {
        //if (nodeVec.back())
        
        // std::cout << (nodeVec.back())->type << endl;
        delete nodeVec.back();
        nodeVec.back() = NULL;
        nodeVec.pop_back();
    }
    //  root = NULL;
}

void handleError() {
    //std::cout << errorFlag << endl;
    if (!errorFlag) clearNode();
    errorFlag = 1;
}