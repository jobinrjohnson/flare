//
// Created by jobinrjohnson on 8/8/20.
//

#include "IfStatementNode.h"

namespace ast {


    NodeType IfStatementNode::getNodeType() {
        return IF_NODE;
    }

    IfStatementNode::IfStatementNode(Node *cond, Node *smt) {

        this->statementList.push_back(smt);
        this->condition.push_back(cond);

    }

    void IfStatementNode::addBranch(Node *cond, Node *smt) {

        this->statementList.push_back(smt);
        this->condition.push_back(cond);

    }

    void IfStatementNode::addElseBranch(Node *smt) {
        this->statementList.push_back(smt);

        auto node = new ValuePlaceholderNode(ConstantInt::get(Type::getInt1Ty(context), 1, false));


        this->condition.push_back(node);
    }

    llvm::Value *IfStatementNode::codegenIfElseIf(int depth) {

        llvm::Function *function = builder.GetInsertBlock()->getParent();
        llvm::BasicBlock *mergeBlock = llvm::BasicBlock::Create(context, "ifCont");

        for (unsigned long i = 0; i < this->condition.size(); ++i) {

            llvm::BasicBlock *elseIfBlock = llvm::BasicBlock::Create(context, "ifCont");
            llvm::BasicBlock *thenBlock = llvm::BasicBlock::Create(context, "thenBlk");

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


    llvm::Value *IfStatementNode::codeGen(int depth) {
        this->printCallStack(depth, "IfStatementNode", __FUNCTION__);
        return this->codegenIfElseIf(depth);
    }
}