//
// Created by jobinrjohnson on 9/23/20.
//

#include "StatementNode.h"

llvm::Value *ast::StatementNode::codeGen(int depth) {

    if (this->type == RETURN) {
        Value *operand = this->operands[0]->codeGen(depth);
        builder.CreateRet(operand);
    }

    return nullptr;
}

ast::StatementNode::StatementNode(ast::StatementType type, Node *node) {
    this->type = type;
    this->operands.push_back(node);
}
