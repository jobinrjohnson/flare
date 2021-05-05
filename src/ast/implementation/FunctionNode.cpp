//
// Created by jobinrjohnson on 05/05/21.
//

#include "FunctionNode.h"

NodeType ast::FunctionNode::getNodeType() {
    return FUNCTION_NODE;
}

llvm::Value *ast::FunctionNode::codeGen(int depth) {

    this->printCallStack(depth, "FunctionNode", __FUNCTION__);


    std::vector<llvm::Type *> argVector(0, llvm::Type::getDoubleTy(context));
    llvm::FunctionType *functionRetType = llvm::FunctionType::get(llvm::Type::getInt32Ty(context),
                                                                  argVector, false);

    llvm::Function *function = llvm::Function::Create(functionRetType, llvm::GlobalValue::ExternalLinkage,
                                                      this->name, module.get());

    this->prepareBlocks(function);

    builder.SetInsertPoint(this->entryBlock);
    AllocaInst *retValue = new AllocaInst(function->getReturnType(), 0, "retVal", this->entryBlock);
    builder.CreateStore(ConstantInt::get(context, APInt(32, 0)), retValue);
    this->statementListNode->codeGen(0);
    builder.CreateBr(this->exitBlock);

    builder.SetInsertPoint(this->exitBlock);
    LoadInst *l = builder.CreateLoad(retValue);
    builder.CreateRet(l);

    llvm::verifyFunction(*function, &(llvm::errs()));


    return nullptr;
}

ast::FunctionNode::FunctionNode(const char *name, ast::StatementListNode *statements) {
    this->name = name;
    this->statementListNode = statements;
}

void ast::FunctionNode::prepareBlocks(llvm::Function *function) {

    this->entryBlock = llvm::BasicBlock::Create(context, "entry", function);
    this->exitBlock = llvm::BasicBlock::Create(context, "exit", function);

}

