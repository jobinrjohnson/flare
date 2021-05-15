//
// Created by jobinrjohnson on 9/23/20.
//

#include <helpers/VariableHelper.h>
#include "StatementNode.h"
#include "FunctionNode.h"

llvm::Value *ast::StatementNode::codeGen(Context *cxt) {

    if (this->type == RETURN) {
        Value *operand = this->operands[0]->codeGen(cxt);

        Node *functionNode = cxt->getCurrentFunction();
        if (functionNode == nullptr) {
            throw "return should be inside a function";
        }
        return dynamic_cast<FunctionNode *>(functionNode)
                ->setFunctionReturn(operand);

    }

    return nullptr;
}

ast::StatementNode::StatementNode(ast::StatementType type, Node *node) {
    this->type = type;
    this->operands.push_back(node);
}
