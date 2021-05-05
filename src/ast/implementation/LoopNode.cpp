//
// Created by jobinrjohnson on 05/05/21.
//

#include "LoopNode.h"

ast::LoopNode::LoopNode(ast::Node *cond, ast::Node *smt) {
    this->condition = cond;
    this->statementList = smt;
}

llvm::Value *ast::LoopNode::codeGen(ast::Context *cxt) {

    this->printCallStack(cxt, "LoopNode", __FUNCTION__);

    Function *insertFunction = builder.GetInsertBlock()->getParent();

    BasicBlock *conditionBlock = BasicBlock::Create(context, "condition", insertFunction);
    BasicBlock *bodyBlock = BasicBlock::Create(context, "body", insertFunction);
    BasicBlock *mergeBlock = BasicBlock::Create(context, "merge", insertFunction);

    // TODO improve this implementation
    builder.CreateBr(conditionBlock);

    builder.SetInsertPoint(conditionBlock);
    builder.CreateCondBr(
            this->condition->codeGen(cxt->nextLevel()),
            bodyBlock,
            mergeBlock
    );

    builder.SetInsertPoint(bodyBlock);
    this->statementList->codeGen(cxt->nextLevel());
    if (bodyBlock->getTerminator() == nullptr) {
        builder.CreateBr(conditionBlock);
    }

    builder.SetInsertPoint(mergeBlock);

    return nullptr;
}

NodeType ast::LoopNode::getNodeType() {
    return LOOP_NODE;
}
