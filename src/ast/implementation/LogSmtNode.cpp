//
// Created by jobinrjohnson on 8/9/20.
//

#include "LogSmtNode.h"

namespace ast {

    NodeType LogSmtNode::getNodeType() {
        return LOG_NODE;
    }

    LogSmtNode::LogSmtNode(Node *exprNode) {
        this->node = exprNode;
    }

    llvm::Value *LogSmtNode::codeGen(int depth) {
        this->printCallStack(depth, "LogSmtNode", __FUNCTION__);

        FunctionType *printfType = FunctionType::get(
                Type::getInt32Ty(context),
                {Type::getInt8PtrTy(context)},
                true
        );
        auto calleeFunction = module->getOrInsertFunction("printf", printfType);
        std::vector<Value *> calleeArgs;

        calleeArgs.push_back(builder.CreateGlobalStringPtr("%d\n", "printfFormat"));
        calleeArgs.push_back(this->node->codeGen(depth + 1));
        return builder.CreateCall(calleeFunction, calleeArgs, "printCall");

    }
}