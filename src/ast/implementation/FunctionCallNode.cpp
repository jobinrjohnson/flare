//
// Created by jobinrjohnson on 08/05/21.
//

#include <ast/FunctionCallNode.h>
#include <exceptions/SemanticException.h>
#include <ast/ExceptionHandleNode.h>
#include <types/ClassObjectType.h>

namespace flare::ast {


    llvm::Value *FunctionCallNode::codeGenObjectCreate(Context *cxt) {

        ClassObjectType *fType = dynamic_cast<ClassObjectType *>(cxt->findType(this->className));
        if (fType == nullptr) {
            throw new exceptions::SemanticException("No declarations for class '"
                                                    + this->className
                                                    + "' found",
                                                    this->lineNumber);
        }
        LValue lvl;
        auto instance = fType->createInstance(lvl);

        auto *function = fType->classDeclNode->getInitFunction();
        std::vector<Value *> calleeArgs;
        calleeArgs.push_back(instance);
        this->performCall(cxt, function, calleeArgs);

        return instance;

    }

    llvm::Value *FunctionCallNode::codeGen(flare::ast::Context *cxt) {

        if (this->isObjectCreation()) {
            return this->codeGenObjectCreate(cxt);
        }

        if (this->isClassFunction()) {
            return this->codeGenObjectFunction(cxt);
        }

        auto calleeFunction = module->getFunction(this->functionName);
        if (calleeFunction == nullptr) {
            throw "Function not declared in the scope";
        }
        if (argumentList == nullptr) {
            return this->performCall(cxt, calleeFunction, None);
        }

        std::vector<Value *> calleeArgs;
        for (ExprNode *element: *(this->argumentList)) {
            calleeArgs.push_back(element->codeGen(cxt->nextLevel()));
        }

        return this->performCall(cxt, calleeFunction, calleeArgs);

    }

    FunctionCallNode::FunctionCallNode(std::string functionName) {
        this->functionName = functionName;
    }

    FunctionCallNode::FunctionCallNode(std::string functionName, std::vector<ExprNode *> *argumentList) {
        this->functionName = functionName;
        this->argumentList = argumentList;
    }

    FunctionCallNode::FunctionCallNode() {}

    llvm::Value *FunctionCallNode::codeGenObjectFunction(Context *cxt) {


        Node *vNode = cxt->findVariable(this->objectName);
        if (vNode == nullptr) {
            throw "no global variable declared in the scope";
        }
        auto *variable = dynamic_cast<VarDeclNode *>(vNode);

        auto fType = variable->getFlareType();
        ClassObjectType *classType;

        if (!(classType = dynamic_cast<ClassObjectType *>(fType))) {
            throw new exceptions::SemanticException("Function '"
                                                    + this->functionName
                                                    + "' is not a class method",
                                                    this->lineNumber);
        }

        auto calleeFunction = module->getFunction(classType->getFullyQualifiedName() + "::" + this->functionName);
        if (calleeFunction == nullptr) {
            throw "Function not declared in the scope";
        }

        std::vector<Value *> calleeArgs;
        calleeArgs.push_back(variable->getLLVMVarRef());
        if (this->argumentList != nullptr) {
            for (ExprNode *element: *(this->argumentList)) {
                calleeArgs.push_back(element->codeGen(cxt->nextLevel()));
            }
        }

        return this->performCall(cxt, calleeFunction, calleeArgs);
    }

    llvm::Value *FunctionCallNode::performCall(Context *cxt, Function *calleeFunction, ArrayRef<Value *> calleeArgs) {

        if (cxt->getCurrentFunction()->hasExceptionHandler()) {
            ExceptionHandleNode *eNode = cxt->getCurrentFunction()->getExceptionHandler();
            return eNode->handleOperation(cxt, [calleeFunction, calleeArgs](BasicBlock *normalBlock,
                                                                            BasicBlock *exceptionBlock) -> Value * {
                return builder.CreateInvoke(
                        calleeFunction,
                        normalBlock,
                        exceptionBlock,
                        calleeArgs
                );

            });
        }

        if (calleeFunction->getReturnType() == llvm::Type::getVoidTy(context)) {
            return builder.CreateCall(calleeFunction, calleeArgs);
        }

        return builder.CreateCall(calleeFunction, calleeArgs, this->functionName);
    }

}