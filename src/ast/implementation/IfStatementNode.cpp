//
// Created by jobinrjohnson on 8/8/20.
//

#include <ast/IfStatementNode.h>

namespace flare::ast {


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

    llvm::Value *IfStatementNode::codegenIfElseIf(Context *cxt) {

        llvm::Function *function = builder.GetInsertBlock()->getParent();
        llvm::BasicBlock *mergeBlock = llvm::BasicBlock::Create(context, "IFmerge");

        for (unsigned long i = 0; i < this->condition.size(); ++i) {

            llvm::BasicBlock *elseIfBlock = llvm::BasicBlock::Create(context, "IFelseif");
            llvm::BasicBlock *thenBlock = llvm::BasicBlock::Create(context, "IFthen");

            builder.CreateCondBr(
                    this->condition[i]->codeGen(cxt->nextLevel()),
                    thenBlock,
                    elseIfBlock
            );

            function->getBasicBlockList().push_back(thenBlock);
            builder.SetInsertPoint(thenBlock);
            this->statementList[i]->codeGen(cxt->nextLevel());
            if (builder.GetInsertBlock()->getTerminator() == nullptr) {
                builder.CreateBr(mergeBlock);
            }
            function->getBasicBlockList().push_back(elseIfBlock);
            builder.SetInsertPoint(elseIfBlock);

            if (i == this->condition.size() - 1 && builder.GetInsertBlock()->getTerminator() == nullptr) {
                builder.CreateBr(mergeBlock);
            }

        }

        function->getBasicBlockList().push_back(mergeBlock);
        builder.SetInsertPoint(mergeBlock);

        return nullptr;

    }


    llvm::Value *IfStatementNode::codeGen(Context *cxt) {
        this->printCallStack(cxt, "IfStatementNode", __FUNCTION__);
        return this->codegenIfElseIf(cxt);
    }

    void IfStatementNode::addBranch(IfStatementNode *node) {

        for (auto element:node->statementList) {
            this->statementList.push_back(element);
        }
        for (auto element:node->condition) {
            this->condition.push_back(element);
        }

        free(node);

    }
}