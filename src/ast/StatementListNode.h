//
// Created by jobinrjohnson on 7/23/20.
//

#ifndef FLARE_STATEMENTLISTNODE_H
#define FLARE_STATEMENTLISTNODE_H


#include "Node.h"
#include "VarDeclNode.h"

namespace ast {

    class StatementListNode : public Node {

    private:
        std::vector<Node *> statements;


    public:

        NodeType getNodeType() {
            return STATEMENT_LIST_NODE;
        }

        StatementListNode() {}

        StatementListNode(Node *node) {
            this->statements.push_back(node);
        }

        void push(Node *node) {
            this->statements.push_back(node);
        }


        void doPrintFinal(Value *valueToPrint) {
            FunctionType *printfType = FunctionType::get(
                    Type::getInt32Ty(llvmContext),
                    {Type::getInt8PtrTy(llvmContext)},
                    true
            );
            auto calleeFunction = modules->getOrInsertFunction("printf", printfType);
            std::vector<Value *> calleeArgs;
            calleeArgs.push_back(builder.CreateGlobalStringPtr("%d\n", "printfFormat"));
            calleeArgs.push_back(valueToPrint);
            builder.CreateCall(calleeFunction, calleeArgs, "printCall");
        }


        llvm::Value *codeGen() {

            Value *finalValue = nullptr;

            std::cout << "Calling StatementListNode@codegen" << "\n";
            for (auto const &value:this->statements) {
                finalValue = value->codeGen();
            }

            if (finalValue != nullptr)
                this->doPrintFinal(finalValue);

            return ConstantInt::get(llvmContext, APInt(32, 0));
        }

    };

}

#endif //FLARE_STATEMENTLISTNODE_H
