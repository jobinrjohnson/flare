//
// Created by jobinrjohnson on 08/05/21.
//

#include <ast/FunctionCallNode.h>
#include <exceptions/SemanticException.h>
#include <ast/ClassDeclNode.h>
#include <ast/helpers/VariableHelper.h>

namespace flare::ast {


    llvm::Value *FunctionCallNode::codeGenObjectCreate(Context *cxt) {

        auto *node = cxt->findClassDeclaration(this->className);
        if (node == nullptr) {
            throw new exceptions::SemanticException("No declarations for class '"
                                                    + this->className
                                                    + "' found",
                                                    this->lineNumber);
        }

        auto *cNode = dynamic_cast<ClassDeclNode *>(node);
        auto *function = cNode->getInitFunction();

        return builder.CreateCall(function, None, this->className + "::.init");

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
            return builder.CreateCall(calleeFunction, None, this->functionName);
        }

        std::vector<Value *> calleeArgs;
        for (ExprNode *element: *(this->argumentList)) {
            calleeArgs.push_back(element->codeGen(cxt->nextLevel()));
        }

        return builder.CreateCall(calleeFunction, calleeArgs, this->functionName);

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

        auto calleeFunction = module->getFunction(this->functionName);
        if (calleeFunction == nullptr) {
            throw "Function not declared in the scope";
        }

        std::vector<Value *> calleeArgs;
        calleeArgs.push_back(builder.CreateLoad(variable->getLLVMVarRef()));
        if (this->argumentList != nullptr) {
            for (ExprNode *element: *(this->argumentList)) {
                calleeArgs.push_back(element->codeGen(cxt->nextLevel()));
            }
        }

        return builder.CreateCall(calleeFunction, calleeArgs, this->functionName);
    }

}