//
// Created by jobinrjohnson on 05/05/21.
//

#include <helpers/VariableHelper.h>
#include "FunctionNode.h"

ast::NodeType ast::FunctionNode::getNodeType() {
    return FUNCTION_NODE;
}

llvm::FunctionType *ast::FunctionNode::codeGenSignature(ast::Context *cxt) {
    std::vector<llvm::Type *> argVector;


    for (Parameter *element: *(this->parameterList)) {
        Type *varType = getLLVMType(element->type->type, context);
        argVector.push_back(varType);
    }

    llvm::FunctionType *functionRetType = llvm::FunctionType::get(getLLVMType(this->type->type, context),
                                                                  argVector, false);
    return functionRetType;
}

llvm::Value *ast::FunctionNode::codeGen(Context *cxt) {

    this->printCallStack(cxt, "FunctionNode", __FUNCTION__);

    cxt->pushFunction(this);

    this->function = llvm::Function::Create(this->codeGenSignature(cxt),
                                            llvm::GlobalValue::ExternalLinkage,
                                            this->name, module.get());

    this->prepareBlocks();

    builder.SetInsertPoint(this->entryBlock);


    // Prepare parameters add to frame
    Function::arg_iterator actualArgs = function->arg_begin();

    for (Parameter *element: *(this->parameterList)) {
        Type *varType = getLLVMType(element->type->type, context);
        auto localVar = new AllocaInst(varType, 0, element->name, this->entryBlock);
        builder.CreateStore(&(*actualArgs), localVar);
        this->statementListNode->createLocal(element->name, localVar);
        ++actualArgs;
    }


    // Prepare return value
    this->retValue = new AllocaInst(function->getReturnType(), 0, ".retVal", this->entryBlock);
//    builder.CreateStore(ConstantInt::get(context, APInt(32, 0)), retValue);

    // Original Function body.
    this->statementListNode->codeGen(cxt);
    if (builder.GetInsertBlock()->getTerminator() == nullptr) {
        builder.CreateBr(this->exitBlock);
    }

    builder.SetInsertPoint(this->exitBlock);
    LoadInst *l = builder.CreateLoad(this->retValue);
    builder.CreateRet(l);

    llvm::verifyFunction(*function, &(llvm::errs()));

    cxt->popFunction();

    return nullptr;
}

ast::FunctionNode::FunctionNode(const char *name, ast::StatementListNode *statements, VarType *type) {
    this->name = name;
    this->statementListNode = statements;
    this->parameterList = new std::vector<ast::Parameter *>();
    this->type = type;
}

void ast::FunctionNode::prepareBlocks() {

    this->entryBlock = llvm::BasicBlock::Create(context, "entry", this->function);
    this->exitBlock = llvm::BasicBlock::Create(context, "exit", this->function);

}

void ast::FunctionNode::setHasMultipleExits() {
    this->hasMultipleExits = true;
}

ast::FunctionNode::FunctionNode(const char *name, ast::StatementListNode *statements, VarType *type,
                                std::vector<ast::Parameter *> *parameterList) {
    this->name = name;
    this->statementListNode = statements;
    this->parameterList = parameterList;
    this->type = type;
}
