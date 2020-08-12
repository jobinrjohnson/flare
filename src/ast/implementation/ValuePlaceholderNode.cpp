//
// Created by jobinrjohnson on 8/9/20.
//

#include "ValuePlaceholderNode.h"

namespace ast {

    NodeType ValuePlaceholderNode::getNodeType() {
        return VALUE_PLACEHOLDER_NODE;
    }

    ValuePlaceholderNode::ValuePlaceholderNode(Value *tempValue) {
        this->value = tempValue;
    }

    llvm::Value *ValuePlaceholderNode::codeGen(int depth) {
        this->printCallStack(depth, "ValuePlaceholderNode", __FUNCTION__);
        return this->value;
    }

}