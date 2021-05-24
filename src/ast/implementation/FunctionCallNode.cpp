//
// Created by jobinrjohnson on 08/05/21.
//

#include <ast/FunctionCallNode.h>
#include <exceptions/SemanticException.h>
#include <ast/ClassDeclNode.h>

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

        return builder.CreateCall(function, None, this->className + ".init");

    }

    llvm::Value *FunctionCallNode::codeGen(flare::ast::Context *cxt) {

        if (this->isObjectCreation()) {
            return this->codeGenObjectCreate(cxt);
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

}