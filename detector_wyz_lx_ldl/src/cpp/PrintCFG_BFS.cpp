#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/BugReporter/BugType.h"
#include "clang/StaticAnalyzer/Core/CheckerRegistry.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h"

#include "clang/Analysis/Analyses/Dominators.h"
#include "clang/Analysis/Analyses/LiveVariables.h"
#include "clang/Analysis/CallGraph.h"
#include "clang/StaticAnalyzer/Core/Checker.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/AnalysisManager.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/ExplodedGraph.h"
#include "clang/StaticAnalyzer/Core/PathSensitive/ExprEngine.h"
#include "llvm/Support/Process.h"

#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

using namespace clang;
using namespace ento;

namespace {

	// Graph node for CFG (Extension: level)
	class myCFGNode
	{
	public:
  		CFGBlock * block;
  		int level = 0;
  		myCFGNode(CFGBlock * arg_block, int arg_level)
    	: block(arg_block), level(arg_level) {}
	};

	class PrintCFG_BFS : public Checker <check::ASTCodeBody> {

	public:
  		void checkASTCodeBody(const Decl *D, AnalysisManager& mgr, BugReporter &BR) const;
	};
} // end anonymous namespace

void PrintCFG_BFS::checkASTCodeBody(const Decl *D, AnalysisManager& mgr,
        BugReporter &BR) const {
    PrintingPolicy Policy(mgr.getLangOpts());
    Policy.TerseOutput = true;
    Policy.PolishForDeclaration = true;
    D->print(llvm::errs(), Policy);
    // Print Function name to stdout.
    D->print(llvm::outs(), Policy);
    cout << endl;
    cerr << endl;

    if (CFG *cfg = mgr.getCFG(D)) {
    
    	int totalBlockNum = cfg -> getNumBlockIDs();
	
		// Sign indicate Searched or Not
    	int * sign = new int[totalBlockNum];
    	for(int i = 0; i < totalBlockNum; i++)
    	{
      		sign[i] = 0;
    	}

		// Queue for BFS
    	queue < myCFGNode *> CFGNodeQueue;

    	CFGBlock & start = cfg -> getEntry();
    	myCFGNode * tmpcfgnode = new myCFGNode(&start, 0); // Initial nodes
    	CFGNodeQueue.push(tmpcfgnode);
    	sign[start.getBlockID()] = 1;

    	while (!CFGNodeQueue.empty())
    	{
      		tmpcfgnode = CFGNodeQueue.front();
      		CFGNodeQueue.pop();
      		CFGBlock * tmpcfgblock = tmpcfgnode -> block;
      		int tmplevel = tmpcfgnode -> level;

      		delete tmpcfgnode;
      		//cout << tmpcfgblock -> getBlockID() << "L: " << tmplevel << endl;
      		cerr << "    " << tmpcfgblock -> getBlockID() << endl;


      		// Reverse CFGBlock
      		CFGTerminator tmpcfgterminator;
      		if(tmpcfgblock -> getTerminator())
      		{
          		tmpcfgterminator = tmpcfgblock -> getTerminator();
          		Stmt *stmt= tmpcfgterminator.getStmt();

          		switch (stmt->getStmtClass()) {
            		case Stmt::DeclStmtClass:
                		break;
            		case Stmt::IfStmtClass: {
              			cout << tmpcfgblock -> getBlockID() << " If " <<  tmplevel << endl;
              			break;
            		}
            		case Stmt::ForStmtClass: {
              			cout << tmpcfgblock -> getBlockID() << " For " <<  tmplevel << endl;
              			break;
            		}
            		case Stmt::WhileStmtClass: {
              			cout << tmpcfgblock -> getBlockID() << " While " << tmplevel << endl;
              			break;
            		}
            		case Stmt::SwitchStmtClass: {
              			cout << tmpcfgblock -> getBlockID() << " Switch " << tmplevel << endl;
              			break;
            		}
            		case Stmt::CXXCatchStmtClass: {
              			break;
            		}
            		default:
              			//cout << "No corresponding type!" << endl;
              		break;
          		}
      		}

      		CFGBlock::succ_iterator succ_start, succ_end;
      
      		for(succ_start = tmpcfgblock -> succ_begin(), succ_end = tmpcfgblock -> succ_end();
      			succ_start != succ_end && succ_start != NULL; succ_start++)
      		{
        		tmpcfgblock = succ_start -> getReachableBlock();
        		if(sign[tmpcfgblock -> getBlockID()] != 1)
        		{
          			//cout << "adjacent nodes" << endl;
          			//cout << tmpcfgblock -> getBlockID() << endl;
          			tmpcfgnode = new myCFGNode(tmpcfgblock, tmplevel + 1);
          			CFGNodeQueue.push(tmpcfgnode);
          			sign[tmpcfgblock -> getBlockID()] = 1;
        		}
      		}
    	}
    	delete[] sign;

      	cfg->dump(mgr.getLangOpts(),
                llvm::sys::Process::StandardErrHasColors());
    }
}

// Register plugin!
extern "C"
void clang_registerCheckers (CheckerRegistry &registry) {
  registry.addChecker<PrintCFG_BFS>("codeclone.PrintCFG_BFS", "Print the sequence of BFS in the CFG.");
}

extern "C"
const char clang_analyzerAPIVersionString[] = CLANG_ANALYZER_API_VERSION_STRING;
