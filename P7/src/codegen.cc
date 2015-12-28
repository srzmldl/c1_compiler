#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <sstream>
#include <iostream>
#include "node.hh"
#include <map>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Pass.h>
#include <llvm/PassManager.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Support/raw_ostream.h>
#include "llvm/Analysis/Passes.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/PassManager.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"

#include <llvm/ADT/SmallVector.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/InlineAsm.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/MathExtras.h>

using namespace llvm;

static Module *TheModule = new Module("c1", getGlobalContext());
// Most of the codes are added with Builder.CreateXXX(...)
    // You may need SetInsertPoint(...) to choose inserted block
    // Learn more in IR/IRBuilder.h
static IRBuilder<> Builder(getGlobalContext());
FunctionPassManager FPM(TheModule);
std::map<std::string, AllocaInst *> NamedValues;
std::map<std::string, GlobalVariable *> NamedValuesGlobal;
static int ifGlobal = 0;

Value *ErrorV(const char *Str) {
    fprintf(stderr, "Error: %s\n", Str);
    return 0;
}

//static Module &TheModule = new Module()
/*Value *codegenDecl(Node *x) {
    if (x->type == VARDECL)
        return ((VarDeclNode*)x)->Codegen();
    else
        return ((ConstDeclNode*)x)->Codegen();
    return 0;
}

Value *codegenStmt(Node *x) {
    switch (x->type) {
    case ASSIGNSTMT:
        return ((AssignStmtNode *)x)->Codegen();
    case CALLSTMT:
        return ((CallStmtNode*)x)->Codegen();
    case IFSTMTNODE:
        return ((IfStmtNode*)x)->Codegen();
    case IFELSESTMTNODE:
        return ((IfElseStmtNode*)x)->Codegen();
    case WHILESTMT:
        return ((WhileStmtNode*)x)->Codegen();
    case COMMASTMT:
        return ((CommaStmtNode*)x)->Codegen();
    case BLOCK:
        return ((BlockNode*)x)->Codegen();
    default:return 0;
    }
}
*/
Value *InputNode::Codegen() {
    //freopen("c1.ll", "w", stderr);
    //FPM.add(createPromoteMemoryToRegisterPass());
    // Add other optimizations if you like.
    FPM.doInitialization();
    ifGlobal = 0;
    for (std::vector<Node*>::iterator it  = comps.begin(); it != comps.end(); it++) {
        if (( *it)->type == FUNCDEF) {
            Function *funcTop = ((FuncDefNode*)(*it))->Codegen();
            FPM.run(*funcTop);
            //funcTop->dump();
        } else {
            ifGlobal = 1;
            Value *valTop = (*it)->Codegen();
            //valTop->dump();
            ifGlobal = 0;
            //return valTop;
        }
    }
    //verifyModule(*TheModule, PrintMessageAction);
    //PassManager PM;
    //PM.add(createPrintModulePass(&outs()));
    //PM.run(*TheModule);
    TheModule->dump();
    return 0;
}

Value *IdentNode::Codegen() {
    Value *V = NamedValues[*name];
    if (V == 0)
      return ErrorV("Unknown variable name");
    return Builder.CreateLoad(V, (*name).c_str());
    //return 0;
}

Value *NumNode::Codegen() {
    return ConstantInt::get(TheModule->getContext(), APInt(32, val));
//return ConstantFP::get(getGlobalContext(), APInt(Val));
}

Value *BinaryExpNode::Codegen() {
    Value *L = lhs->Codegen();
    Value *R = rhs->Codegen();
    if (L == 0 || R == 0)
        return 0;
    switch (op) {
    case '+':
        return Builder.CreateAdd(L, R, "addtmp");
    case '-':
        return Builder.CreateSub(L, R, "subtmp");
    case '*':
        return Builder.CreateMul(L, R, "multmp");
    case '/':
        return Builder.CreateSDiv(L, R, "divtmp");
    case '%':
        return Builder.CreateSRem(L, R, "modrem");
    default:
        break;
    }
}

Value *UnaryExpNode::Codegen() {
    Value *OperandV = operand->Codegen();
    if (OperandV == 0) return 0;
    if (op == '+') return OperandV;
    return Builder.CreateSub(ConstantInt::get(TheModule->getContext(), APInt(32, 0)), OperandV, "unopsub");
}

//return to do
Value *BlockNode::Codegen() {
    for (Node *p = blockList; p != NULL; p = p->next) {
        Value *tmp = p->Codegen();//codegenDecl(p);
        //if (tmp == 0) tmp = codegenStmt(p);
        if (p->next == NULL) return tmp;
    }
    return 0;
}

Value *CondNode::Codegen() {
    Value *L = lhs->Codegen();
    Value *R = rhs->Codegen();
    if (L == 0 || R == 0) return 0;
    if ((*RelOp) == "==")
        return Builder.CreateICmpEQ(L, R, "eq");
    if ((*RelOp) == "!=")
        return Builder.CreateICmpNE(L, R, "ne");
    if ((*RelOp) == "<=")
        return Builder.CreateICmpSLE(L, R, "eq");
    if ((*RelOp) == ">=")
        return Builder.CreateICmpSGE(L, R, "ne");
    if ((*RelOp) == "<")
        return Builder.CreateICmpSLT(L, R, "eq");
    if ((*RelOp) == ">")
        return Builder.CreateICmpSGT(L, R, "ne");
    return 0;
}

Value *ConstDefEleNode::Codegen() {
    Value *val = exp->Codegen();
}

Value *ConstDefArrLimNode::Codegen() {
}

Value *ConstDefArrNoLimNode::Codegen() {
}

Value *ConstDeclNode::Codegen() {
}

Value *VarDefEleNoEquNode::Codegen() {
    //Constant *FooVal = ConstantInt::get(TheModule->getContext(), APInt(32, 10));
    // printf("!!!");
    if (!ifGlobal) {
        AllocaInst *Foo = Builder.CreateAlloca(IntegerType::get(TheModule->getContext(), 32), 0, ident->name->c_str());
        NamedValues[*(ident->name)] = Foo;
        //  Foo->dump();
        return Foo;
    } else {
        GlobalVariable *Foo =
            new GlobalVariable(*TheModule, IntegerType::get(TheModule->getContext(), 32), false, GlobalValue::ExternalLinkage, 0, ident->name->c_str());
        NamedValuesGlobal[*(ident->name)] = Foo;
        ConstantInt* const_int32 = ConstantInt::get(TheModule->getContext(), APInt(32, StringRef("0"), 10));
        Foo->setInitializer(const_int32);
        return Foo;
    }
//Builder.CreateStore(FooVal, Foo);
    //  ConstantInt *defval = ConstantInt::get(TheModule->getContext(), APInt(32, 0));
    //AllocaInst *val = Builder.CreateAlloca(IntegerType::get(TheModule->getContext(), 32), 0, ident->name->c_str());
    //Builder.CreateStore(defval, val);
}

Value *VarDefArrLimNoEquNode::Codegen() {
}

Value *VarDefEleEquNode::Codegen() {
}

Value *VarDefArrNoLimEquNode::Codegen() {
}

Value *VarDefArrLimEquNode::Codegen() {
}

Value *VarDeclNode::Codegen() {
    for (Node *p = varDefList; p; p = p->next) {
        //printf("%d\n", p->type);
        Value *tmp = p->Codegen();
        if (p->next == NULL) return tmp;
    }
}

Function *FuncDefNode::Codegen() {
    std::vector<Type*> theFuncArgs;
    FunctionType *theFuncType =
        FunctionType::get(Type::getVoidTy(TheModule->getContext()),
                theFuncArgs, false);
    Function *theFunc = Function::Create(theFuncType, GlobalValue::ExternalLinkage, ident->name->c_str(), TheModule);
    BasicBlock *EntryBB = BasicBlock::Create(TheModule->getContext(), "entry", theFunc, 0);
    Builder.SetInsertPoint(EntryBB);
    block->Codegen();
    return theFunc;
}
//array TODO
Value *AssignStmtNode::Codegen() {
    Value *Val = exp->Codegen();
    if (Val == 0) return 0;
    Value *Variable = NamedValues[*(((IdentNode *)LVal)->name)];
    Builder.CreateStore(Val, Variable);
    return Val;
}

Value *CallStmtNode::Codegen() {
/*    ident->Codegen();
    Function *CalleeF = TheModule->getFunction(*(ident->name));
    if (CalleeF == 0)
        return ErrorV("Unknown function referenced");
    //if (CalleeF)
    std::vector <Value *> ArgsV;
    return Builder.CreateCall(CalleeF, ArgsV, "calltmp");*/
}

Value *IfStmtNode::Codegen() {
    /*
    Value *CondV = cond->Codegen();
    if (CondV == 0)
        return 0;

    // Convert condition to a bool by comparing equal to 0.0.
    CondV = Builder.CreateFCmpONE(
        CondV, ConstantFP::get(getGlobalContext(), APFloat(true)), "ifcond");

    Function *TheFunction = Builder.GetInsertBlock()->getParent();

    // Create blocks for the then and else cases.  Insert the 'then' block at the
  // end of the function.
    BasicBlock *ThenBB =
        BasicBlock::Create(getGlobalContext(), "then", TheFunction);
    BasicBlock *MergeBB = BasicBlock::Create(getGlobalContext(), "ifcont");

    Builder.CreateCondBr(CondV, ThenBB, MergeBB);

    // Emit then value.
    Builder.SetInsertPoint(ThenBB);

    Value *ThenV = stmt->Codegen();
    if (ThenV == 0)
        return 0;
    
    Builder.CreateBr(MergeBB);
    // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
    ThenBB = Builder.GetInsertBlock();
    
    TheFunction->getBasicBlockList().push_back(MergeBB);
    Builder.SetInsertPoint(MergeBB);
    PHINode *PN =
        Builder.CreatePHI(Type::getDoubleTy(getGlobalContext()), 2, "iftmp");

    PN->addIncoming(ThenV, ThenBB);
    //PN->addIncoming(ElseV, ElseBB);
    return PN; */
}

Value *IfElseStmtNode::Codegen() {
    /*
    Value *CondV = cond->Codegen();
    if (CondV == 0)
        return 0;

    // Convert condition to a bool by comparing equal to 0.0.
    CondV = Builder.CreateFCmpONE(
        CondV, ConstantFP::get(getGlobalContext(), APInt(0)), "ifcond");

    Function *TheFunction = Builder.GetInsertBlock()->getParent();
    
    // Create blocks for the then and else cases.  Insert the 'then' block at the
  // end of the function.
    BasicBlock *ThenBB =
        BasicBlock::Create(getGlobalContext(), "then", TheFunction);
    BasicBlock *ElseBB = BasicBlock::Create(getGlobalContext(), "else");
    BasicBlock *MergeBB = BasicBlock::Create(getGlobalContext(), "ifcont");

    Builder.CreateCondBr(CondV, ThenBB, ElseBB);
    
    // Emit then value.
    Builder.SetInsertPoint(ThenBB);
    
    Value *ThenV = thenStmt->Codegen();
    if (ThenV == 0)
        return 0;
    
    Builder.CreateBr(MergeBB);
    // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
    ThenBB = Builder.GetInsertBlock();
    
    // Emit else block.
    TheFunction->getBasicBlockList().push_back(ElseBB);
    Builder.SetInsertPoint(ElseBB);
    
    Value *ElseV = elseStmt->Codegen();
    if (ElseV == 0)
        return 0;
    
    Builder.CreateBr(MergeBB);
    ElseBB = Builder.GetInsertBlock();
    
    // Emit merge block.
    // Codegen of 'Else' can change the current block, update ElseBB for the PHI.
    TheFunction->getBasicBlockList().push_back(MergeBB);
    Builder.SetInsertPoint(MergeBB);
    PHINode *PN =
        Builder.CreatePHI(Type::getDoubleTy(getGlobalContext()), 2, "iftmp");

    PN->addIncoming(ThenV, ThenBB);
    PN->addIncoming(ElseV, ElseBB);
    return PN;
    */
}

Value *WhileStmtNode::Codegen() {
}

Value *CommaStmtNode::Codegen() {
    return 0;
}

Value *RefArrNode::Codegen() {
}
