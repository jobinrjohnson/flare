//
// Created by jobinrjohnson on 05/05/21.
//

#include <ast/LoopNode.h>

namespace flare::ast {

    LoopNode::LoopNode(Node *cond, Node *smt) {
        this->condition = cond;
        this->statementList = smt;
    }

    llvm::Value *LoopNode::codeGen(Context *cxt) {

        this->printCallStack(cxt, "LoopNode", __FUNCTION__);


        if (this->preLoop != nullptr) {
            this->preLoop->codeGen(cxt->nextLevel());
        }

        Function *insertFunction = builder.GetInsertBlock()->getParent();

        BasicBlock *conditionBlock = BasicBlock::Create(context, "loopCondition", insertFunction);
        BasicBlock *bodyBlock = BasicBlock::Create(context, "loopBody", insertFunction);
        BasicBlock *mergeBlock = BasicBlock::Create(context, "loopMerge", insertFunction);

        // TODO improve this implementation
        builder.CreateBr(conditionBlock);

        builder.SetInsertPoint(conditionBlock);
        builder.CreateCondBr(
                this->condition->codeGen(cxt->nextLevel()),
                bodyBlock,
                mergeBlock
        );

        builder.SetInsertPoint(bodyBlock);
        if (this->before != nullptr) {
            this->before->codeGen(cxt->nextLevel());
        }
        this->statementList->codeGen(cxt->nextLevel());
        if (this->after != nullptr) {
            this->after->codeGen(cxt->nextLevel());
        }
        if (builder.GetInsertBlock()->getTerminator() == nullptr) {
            builder.CreateBr(conditionBlock);
        }

        builder.SetInsertPoint(mergeBlock);

        return nullptr;
    }

    NodeType LoopNode::getNodeType() {
        return LOOP_NODE;
    }
}
