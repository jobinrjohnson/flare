//
// Created by jobinrjohnson on 8/9/20.
//

#include <ast/LogSmtNode.h>

namespace flare::ast {

    NodeType LogSmtNode::getNodeType() {
        return LOG_NODE;
    }

    LogSmtNode::LogSmtNode(Node *exprNode) {
        this->node = exprNode;
    }

    llvm::Value *LogSmtNode::codeGen(Context *cxt) {
        this->printCallStack(cxt, "LogSmtNode", __FUNCTION__);

        Value *printValue = this->node->codeGen(cxt);

        FunctionType *printfType = FunctionType::get(
                Type::getInt32Ty(context),
                {Type::getInt8PtrTy(context)},
                true
        );
        auto calleeFunction = module->getOrInsertFunction("printf", printfType);
        std::vector<Value *> calleeArgs;

        std::string formatter;
        switch (printValue->getType()->getTypeID()) {

            case llvm::Type::HalfTyID:
            case llvm::Type::FloatTyID:
            case llvm::Type::DoubleTyID:
                formatter = "%f\n";
                break;
            case llvm::Type::IntegerTyID:
                formatter = "%ld\n";
                break;

            default:
                formatter = "%s\n";
                break;
        }


        calleeArgs.push_back(builder.CreateGlobalStringPtr(formatter, "printfFormat"));
        calleeArgs.push_back(printValue);
        return builder.CreateCall(calleeFunction, calleeArgs, "printCall");

    }
}