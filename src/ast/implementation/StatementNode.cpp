//
// Created by jobinrjohnson on 9/23/20.
//

#include "StatementNode.h"

llvm::Value *ast::StatementNode::codeGen(Context *cxt) {

    if (this->type == RETURN) {
        Value *operand = this->operands[0]->codeGen(cxt);
        builder.CreateRet(operand);
    }

    return nullptr;
}

ast::StatementNode::StatementNode(ast::StatementType type, Node *node) {
    this->type = type;
    this->operands.push_back(node);
}
