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
#include "llvm/IR/Verifier.h"
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

static int nowLevel = 0;
struct varLevelNode {
    int level;
    bool isNew;
    std::string name;
    AllocaInst *old;
    varLevelNode (int level = 0, bool isNew = true, std::string name = "", AllocaInst *old = NULL) : level(level), isNew(isNew), name(name), old(old) {}
};

static std::vector< varLevelNode > varVector;

Value *ErrorV(const char *Str) {
    fprintf(stderr, "Error: %s\n", Str);
    return 0;
}
void createNewMap(std::string name, AllocaInst* alloc) {
    int isNew = 1;
    AllocaInst *old = NULL;
    if (NamedValues[name]) isNew = 0, old = NamedValues[name];
    varVector.push_back(varLevelNode(nowLevel, isNew, name, old));
    NamedValues[name] = alloc;
}

Value *InputNode::Codegen() {
    //freopen("c1.ll", "w", stderr);
    //FPM.add(createPromoteMemoryToRegisterPass());
    // Add other optimizations if you like.
    FPM.doInitialization();
    for (std::vector<Node*>::iterator it  = comps.begin(); it != comps.end(); it++) {
        if (( *it)->type == FUNCDEF) {
            Function *funcTop = ((FuncDefNode*)(*it))->Codegen();
            FPM.run(*funcTop);
            //funcTop->dump();
        } else {
            Value *valTop = (*it)->Codegen();
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
    if (V) 
        return Builder.CreateLoad(V, (*name).c_str());
    V = NamedValuesGlobal[*name];
    if (V == 0)
        return ErrorV("can not find variable");
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
    ++nowLevel;
    Value *tmp = 0;
    for (Node *p = blockList; p != NULL; p = p->next) {
        tmp = p->Codegen();//codegenDecl(p);
        //if (tmp == 0) tmp = codegenStmt(p);
    }
    for (; !varVector.empty() && varVector.back().level == nowLevel; varVector.pop_back()) {
        varLevelNode tmp = varVector.back();
        if (tmp.isNew) NamedValues.erase(tmp.name);
        else NamedValues[tmp.name] = tmp.old;
    }
    --nowLevel;
    return tmp;
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
    if (nowLevel > 0) {
        AllocaInst *Foo = Builder.CreateAlloca(IntegerType::get(TheModule->getContext(), 32), 0, ident->name->c_str());
        createNewMap(*(ident->name), Foo);
        Builder.CreateStore(val, Foo, false);
        return Foo;
    } else {
        GlobalVariable *Foo =
            new GlobalVariable(*TheModule, IntegerType::get(TheModule->getContext(), 32), false, GlobalValue::ExternalLinkage, 0, ident->name->c_str());
        NamedValuesGlobal[*(ident->name)] = Foo;
        ConstantInt* const_int32 = ConstantInt::get(TheModule->getContext(), APInt(32, ((NumNode *)exp)->val, 10));
        Foo->setInitializer(const_int32);
        return Foo;
    }
}

Value *ConstDefArrLimNode::Codegen() {
}

Value *ConstDefArrNoLimNode::Codegen() {
}

Value *ConstDeclNode::Codegen() {
    for (Node *p = constDefLink; p; p = p->next) {
        //printf("%d\n", p->type);
        Value *tmp = p->Codegen();
        if (p->next == NULL) return tmp;
    }
}

Value *VarDefEleNoEquNode::Codegen() {
    //Constant *FooVal = ConstantInt::get(TheModule->getContext(), APInt(32, 10));
    // printf("!!!");
    if (nowLevel > 0) {
        AllocaInst *Foo = Builder.CreateAlloca(IntegerType::get(TheModule->getContext(), 32), 0, ident->name->c_str());
        createNewMap(*(ident->name), Foo);
        return Foo;
    } else {
        GlobalVariable *Foo =
            new GlobalVariable(*TheModule, IntegerType::get(TheModule->getContext(), 32), false, GlobalValue::ExternalLinkage, 0, ident->name->c_str());
        NamedValuesGlobal[*(ident->name)] = Foo;
        ConstantInt* const_int32 = ConstantInt::get(TheModule->getContext(), APInt(32, StringRef("0"), 10));
        Foo->setInitializer(const_int32);
        return Foo;
    }
}

Value *VarDefArrLimNoEquNode::Codegen() {
    int val = ((NumNode *)lim)->val;
    ArrayType *TheArrayType = ArrayType::get(IntegerType::get(TheModule->getContext(), 32), val);
    if (nowLevel > 0) {
        AllocaInst* Foo = Builder.CreateAlloca(TheArrayType, 0, ident->name->c_str());
        createNewMap(*(ident->name), Foo);
        return Foo;
    } else {
        GlobalVariable *Foo =
            new GlobalVariable(*TheModule, TheArrayType, false, GlobalValue::ExternalLinkage, 0, ident->name->c_str());
        NamedValuesGlobal[*(ident->name)] = Foo;
        //ConstantInt* const_int32 = ConstantInt::get(TheModule->getContext(), APInt(32, StringRef("0"), 10));
        //Foo->setInitializer(const_int32);
        return Foo;
    }

    //Builder.CreateGEP(ptr, ident->name->c_str())
}

Value *VarDefEleEquNode::Codegen() {
    Value* val = exp->Codegen();
    if (nowLevel > 0) {
        AllocaInst *Foo = Builder.CreateAlloca(IntegerType::get(TheModule->getContext(), 32), 0, ident->name->c_str());
        createNewMap(*(ident->name), Foo);
        Builder.CreateStore(val, Foo, false);
        return Foo;
    } else {
        GlobalVariable *Foo =
            new GlobalVariable(*TheModule, IntegerType::get(TheModule->getContext(), 32), false, GlobalValue::ExternalLinkage, 0, ident->name->c_str());
        NamedValuesGlobal[*(ident->name)] = Foo;
        ConstantInt* const_int32 = ConstantInt::get(TheModule->getContext(), APInt(32, ((NumNode *)exp)->val, 10));
        Foo->setInitializer(const_int32);
        return Foo;
    }
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
    if ((*ident->name) == "print") {
        std::vector<Type*> func_print_args;
        FunctionType *func_print_type =
            FunctionType::get(Type::getInt32Ty(getGlobalContext()),func_print_args, false);
        Function *func_print = Function::Create(
            func_print_type, GlobalValue::ExternalLinkage, "print", TheModule);
        
        //Builder.CreateCall(func_print);
        ConstantInt *RetVal = ConstantInt::get(getGlobalContext(), APInt(32, 0));
        Builder.CreateRet(RetVal);
        return func_print;
    }
    
    int arg_size = 0;
    std::vector<Type*> theFuncArgs(arg_size, Type::getInt32Ty(getGlobalContext()));
    FunctionType *theFuncType =
        FunctionType::get(Type::getInt32Ty(getGlobalContext()), theFuncArgs, false);

    Function *theFunc = Function::Create(theFuncType, Function::ExternalLinkage, ident->name->c_str(), TheModule);
//    theFunc->setCallingConv(CallingConv::C);
    BasicBlock *EntryBB = BasicBlock::Create(getGlobalContext(), "entry", theFunc);
    Builder.SetInsertPoint(EntryBB);
    block->Codegen();
    
    EntryBB = Builder.GetInsertBlock();
    ConstantInt *RetVal = ConstantInt::get(getGlobalContext(), APInt(32, 0));
    Builder.CreateRet(RetVal);
    return theFunc;
}
//array TODO
Value *AssignStmtNode::Codegen() {
    Value *Val = exp->Codegen();
    if (Val == 0) return 0;
    if (LVal->type == IDENT) {
        Value *Variable = NamedValues[*(((IdentNode *)LVal)->name)];
        if (!Variable)
            Variable = NamedValuesGlobal[*(((IdentNode *)LVal)->name)];
        if (!Variable)
            ErrorV("can not find variable");
        return Builder.CreateStore(Val, Variable);
    } else {
        std::string name = *(((RefArrNode*)LVal)->ident->name);
           AllocaInst *ptr = NamedValues[name];
    //if (!ptr) ptr = NamedValuesGlobal[name];
           Value *val = ((RefArrNode*)LVal)->exp->Codegen();
    
    //CastInst* int64_idxprom = new SExtInst(val, IntegerType::get(TheModule->getContext(), 64), "idxprom");
    //ConstantInt* const_int32_7 = ConstantInt::get(TheModule->getContext(), APInt(32, StringRef("0"), 10));
    
    //std::vector<Value*> ptr_arrayidx_indices;
    // ptr_arrayidx_indices.push_back(const_int32_7);
    //ptr_arrayidx_indices.push_back(int64_idxprom);
           std::vector<llvm::Value *> tmp_args;
           tmp_args.push_back(Builder.getInt32(0));
           tmp_args.push_back(val);
    //return ptr[val];
           Value *tmp = Builder.CreateGEP(ptr, tmp_args, "getArr");
           Builder.CreateStore(Val, tmp);
        /*std::vector<Value*> ptr_arrayidx_indices;
        ConstantInt* const_int32_5 = ConstantInt::get(mod->getContext(), APInt(32, StringRef("0"), 10));

        LoadInst* int32_12 = new LoadInst(ptr_c, "", false);
        CastInst* int64_idxprom = new SExtInst(int32_12, IntegerType::get(mod->getContext(), 64), "idxprom");
        ptr_arrayidx_indices.push_back(const_int32_5);
        ptr_arrayidx_indices.push_back(int64_idxprom);*/
    }
    return Val;
}

Value *CallStmtNode::Codegen() {
    //ident->Codegen();
    Function *CalleeF = TheModule->getFunction(*(ident->name));
    //CallInst *CallerF = CallInst::Create(CalleeF, "calltmp");
    if (CalleeF == 0)
        return ErrorV("Unknown function referenced");
    //if (CalleeF)
    std::vector<Value*> theFuncArgs;
    return Builder.CreateCall(CalleeF);
    //return Builder.CreateCall(CalleeF, theFuncArgs, "calltmp");
    //CallInst* caller = CallInst::Create(CalleeF, "");
    //caller->setCallingConv(CallingConv::C);
    //caller->setTailCall(false);
    //Builder.Insert(caller, "tmpcall");
    //return caller;

}

Value *IfStmtNode::Codegen() {
    Value *CondV = cond->Codegen();
    if (CondV == 0)
        return 0;

    // Convert condition to a bool by comparing equal to 0.0.
    //CondV = Builder.CreateFCmpONE(
    //  CondV, ConstantFP::get(getGlobalContext(), APInt(0)), "ifcond");

    Function *TheFunction = Builder.GetInsertBlock()->getParent();
    // Create blocks for the then and else cases.  Insert the 'then' block at the
  // end of the function.
    BasicBlock *ThenBB =
        BasicBlock::Create(getGlobalContext(), "if.then", TheFunction);
    BasicBlock *MergeBB = BasicBlock::Create(getGlobalContext(), "if.end", TheFunction);

    Builder.CreateCondBr(CondV, ThenBB, MergeBB);

    // Emit then value.
    Builder.SetInsertPoint(ThenBB);

    Value *ThenV = stmt->Codegen();
    if (ThenV == 0)
        return 0;

    Builder.CreateBr(MergeBB);
    // Codegen of 'Then' can change the current block, update ThenBB for the PHI.
    ThenBB = Builder.GetInsertBlock();

    // Emit else block.
    //TheFunction->getBasicBlockList().push_back(ElseBB);
    Builder.SetInsertPoint(MergeBB);
    
    //Builder.CreateBr(MergeBB);
    //PHINode *PN =
    //Builder.CreatePHI(Type::getDoubleTy(getGlobalContext()), 2, "iftmp");

        //PN->addIncoming(ThenV, ThenBB);
        //PN->addIncoming(ElseV, ElseBB);
        //return PN;
    return 0;
}

Value *IfElseStmtNode::Codegen() {
    Value *CondV = cond->Codegen();
    if (CondV == 0)
        return 0;

    // Convert condition to a bool by comparing equal to 0.0.
    //CondV = Builder.CreateFCmpONE(
    //  CondV, ConstantFP::get(getGlobalContext(), APInt(0)), "ifcond");

    Function *TheFunction = Builder.GetInsertBlock()->getParent();
    
    // Create blocks for the then and else cases.  Insert the 'then' block at the
  // end of the function.
    BasicBlock *ThenBB =
        BasicBlock::Create(getGlobalContext(), "if.then", TheFunction);
    BasicBlock *ElseBB = BasicBlock::Create(getGlobalContext(), "if.else", TheFunction);
    BasicBlock *MergeBB = BasicBlock::Create(getGlobalContext(), "if.end", TheFunction);

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
    //TheFunction->getBasicBlockList().push_back(ElseBB);
    Builder.SetInsertPoint(ElseBB);
    
    Value *ElseV = elseStmt->Codegen();
    if (ElseV == 0)
        return 0;
    
    //ElseBB = Builder.GetInsertBlock();
    Builder.CreateBr(MergeBB);
    
    //Builder.CreateBr(MergeBB);
    // Emit merge block.
    // Codegen of 'Else' can change the current block, update ElseBB for the PHI.
    //TheFunction->getBasicBlockList().push_back(MergeBB);
    //MergeBB = Builder.GetInsertBlock();
    ElseBB = Builder.GetInsertBlock();
    Builder.SetInsertPoint(MergeBB);
    //PHINode *PN =
    //Builder.CreatePHI(Type::getDoubleTy(getGlobalContext()), 2, "iftmp");

    //PN->addIncoming(ThenV, ThenBB);
    //PN->addIncoming(ElseV, ElseBB);
    //return PN;
    return 0;
}

Value *WhileStmtNode::Codegen() {
    Function *TheFunction = Builder.GetInsertBlock()->getParent();
    
    BasicBlock *CondBB =
        BasicBlock::Create(getGlobalContext(), "while.cond", TheFunction);
    BasicBlock *LoopBB =
        BasicBlock::Create(getGlobalContext(), "while.loop", TheFunction);
    BasicBlock *WhileEndBB =
        BasicBlock::Create(getGlobalContext(), "while.end", TheFunction);
    
    Builder.CreateBr(CondBB);
    Builder.SetInsertPoint(CondBB);
    Value *CondV = cond->Codegen();
    Builder.CreateCondBr(CondV, LoopBB, WhileEndBB);

    // Emit then value.
    Builder.SetInsertPoint(LoopBB);

    Value *LoopV = stmt->Codegen();
    if (LoopV == 0)
        return 0;

    LoopV = Builder.GetInsertBlock();
    Builder.CreateBr(CondBB);

    Builder.SetInsertPoint(WhileEndBB);
    return 0;
}

Value *CommaStmtNode::Codegen() {
    return NULL;
}

Value *RefArrNode::Codegen() {
    std::string name = *(ident->name);
    AllocaInst *ptr = NamedValues[name];
    //if (!ptr) ptr = NamedValuesGlobal[name];
    Value *val = exp->Codegen();
    
    //CastInst* int64_idxprom = new SExtInst(val, IntegerType::get(TheModule->getContext(), 64), "idxprom");
    //ConstantInt* const_int32_7 = ConstantInt::get(TheModule->getContext(), APInt(32, StringRef("0"), 10));
    
    //std::vector<Value*> ptr_arrayidx_indices;
    // ptr_arrayidx_indices.push_back(const_int32_7);
    //ptr_arrayidx_indices.push_back(int64_idxprom);
    std::vector<llvm::Value *> tmp_args;
    tmp_args.push_back(Builder.getInt32(0));
    tmp_args.push_back(val);
    //return ptr[val];
    Value *tmp = Builder.CreateGEP(ptr, tmp_args, "getArr");
    //Value *tmp = Builder.CreateGEP(ptr, 1);
//    return tmp;
    return Builder.CreateLoad(tmp, "refArr");
    /*Values ptr_arrayidx = GetElementPtrInst::Create(ptr, ptr_arrayidx_indices, "arrayidx");
      return new LoadInst(ptr_arrayidx, "", false, label_entry);*/
}
