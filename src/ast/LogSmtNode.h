//
// Created by jobinrjohnson on 8/9/20.
//

#ifndef FLARE_LOGSMTNODE_H
#define FLARE_LOGSMTNODE_H


#include "Node.h"

namespace ast {
    class LogSmtNode : public Node {

        Node *node;


    public:

        NodeType getNodeType() {
            return LOG_NODE;
        }

        LogSmtNode(Node *exprNode) {
            this->node = exprNode;
        }

        llvm::Value *codeGen(int depth) {
            this->printCallStack(depth, "LogSmtNode", __FUNCTION__);

            FunctionType *printfType = FunctionType::get(
                    Type::getInt32Ty(llvmContext),
                    {Type::getInt8PtrTy(llvmContext)},
                    true
            );
            auto calleeFunction = modules->getOrInsertFunction("printf", printfType);
            std::vector<Value *> calleeArgs;

            calleeArgs.push_back(builder.CreateGlobalStringPtr("%d\n", "printfFormat"));
            calleeArgs.push_back(this->node->codeGen(depth + 1));
            return builder.CreateCall(calleeFunction, calleeArgs, "printCall");

        }


    };

}

#endif //FLARE_LOGSMTNODE_H
