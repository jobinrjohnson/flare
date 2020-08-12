//
// Created by jobinrjohnson on 8/3/20.
//

#include "AssignmentNode.h"

namespace ast {

    AssignmentNode::AssignmentNode(char *name, Node *node) {
        this->varName = name;
        this->expression = node;
    }

    llvm::Value *AssignmentNode::codeGen(int depth) {
        this->printCallStack(depth, "AssignmentNode", __FUNCTION__);

        auto variable = module->getGlobalVariable(this->varName);
        Value *value = this->expression->codeGen(depth + 1);
        return builder.CreateStore(value, variable);
    }

    NodeType AssignmentNode::getNodeType() {
        return ASSIGNMENT_NODE;
    }

}