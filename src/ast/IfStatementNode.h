//
// Created by jobinrjohnson on 8/8/20.
//

#ifndef FLARE_IFSTATEMENTNODE_H
#define FLARE_IFSTATEMENTNODE_H


#include "Node.h"
#include "ValuePlaceholderNode.h"

namespace ast {

    class IfStatementNode : public Node {

        std::vector<Node *> statementList;
        std::vector<Node *> condition;

    public:


        NodeType getNodeType() override {
            return IF_NODE;
        }

        IfStatementNode(Node *cond, Node *smt) {

            this->statementList.push_back(smt);
            this->condition.push_back(cond);

        }

        void addBranch(Node *cond, Node *smt) {

            this->statementList.push_back(smt);
            this->condition.push_back(cond);

        }

        void addElseBranch(Node *smt) {
            this->statementList.push_back(smt);

            auto node = new ValuePlaceholderNode(ConstantInt::get(Type::getInt1Ty(llvmContext), 1, false));


            this->condition.push_back(node);
        }


        IfStatementNode(Node *cond, Node *smts, Node *smts2) {

            this->statementList.push_back(smts);
            this->statementList.push_back(smts2);
            this->condition.push_back(cond);

        }


        llvm::Value *codegenIfElseIf(int depth) {

            llvm::Function *function = builder.GetInsertBlock()->getParent();
            llvm::BasicBlock *mergeBlock = llvm::BasicBlock::Create(llvmContext, "ifCont");

            for (unsigned long i = 0; i < this->condition.size(); ++i) {

                llvm::BasicBlock *elseIfBlock = llvm::BasicBlock::Create(llvmContext, "ifCont");
                llvm::BasicBlock *thenBlock = llvm::BasicBlock::Create(llvmContext, "thenBlk");

                builder.CreateCondBr(
                        this->condition[i]->codeGen(depth + 1),
                        thenBlock,
                        elseIfBlock
                );

                function->getBasicBlockList().push_back(thenBlock);
                builder.SetInsertPoint(thenBlock);
                this->statementList[i]->codeGen(depth + 1);
                builder.CreateBr(mergeBlock);

                function->getBasicBlockList().push_back(elseIfBlock);
                builder.SetInsertPoint(elseIfBlock);

                if (i == this->condition.size() - 1) {
                    builder.CreateBr(mergeBlock);
                }

            }

            function->getBasicBlockList().push_back(mergeBlock);
            builder.SetInsertPoint(mergeBlock);

            return nullptr;


        }


        llvm::Value *codeGen(int depth) override {
            this->printCallStack(depth, "IfStatementNode", __FUNCTION__);

            return this->codegenIfElseIf(depth);

        }

    };

}


#endif //FLARE_IFSTATEMENTNODE_H
